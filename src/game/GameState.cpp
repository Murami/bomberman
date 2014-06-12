#include <iterator>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <SDL.h>
#include "PauseState.hh"
#include "game/Tile.hh"
#include "game/GameState.hh"
#include "game/GameManager.hh"

#include "events/Input.hh"
#include "events/IEventListener.hh"

#include "graphic/Camera.hh"
#include "graphic/Screen.hh"
#include "graphic/ProjectionOrtho2D.hh"
#include "graphic/ProjectionPerspective.hh"
#include "graphic/RenderState.hh"
#include "graphic/IDrawable.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"

#include "entity/AEntity.hh"
#include "entity/GameBox.hh"
#include "entity/FireBonus.hh"
#include "entity/SpeedBonus.hh"
#include "entity/BombBonus.hh"
#include "entity/MultiBombBonus.hh"
#include "entity/DarkBonus.hh"
#include "entity/BoxBonus.hh"
#include "entity/PowerBonus.hh"
#include "entity/RandomBonus.hh"
#include "entity/WaterBonus.hh"
#include "entity/EntityFactory.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"

namespace bbm
{
  GameState::GameState(GameManager& manager,
		       GameStateConfig* config) :
    _tilemap(),
    _manager(manager),
    _config(config)
  {
  }

  GameState::~GameState()
  {
  }

  void			GameState::randomize(int x, int y)
  {
    int			posx;
    int			posy;

    _tilemap.randomize(x, y);
    for (posx = 1; posx < x - 1; posx++)
      {
	for(posy = 1; posy < y - 1; posy++)
	  {
	    if (_tilemap.getTileType(posx, posy) != Tile::Spawn &&
		_tilemap.getTileType(posx + 1, posy) != Tile::Spawn &&
		_tilemap.getTileType(posx - 1, posy) != Tile::Spawn &&
		_tilemap.getTileType(posx, posy + 1) != Tile::Spawn &&
		_tilemap.getTileType(posx, posy - 1) != Tile::Spawn &&
		std::rand() % 2 == 1)
	      addEntity(new GameBox(glm::vec2(posx, posy), -1, *this));
	  }
      }
  }

  void			GameState::load(const std::string & file)
  {
    Serializer		s = Serializer::create<JSONSerializer>();
    try
      {
	s->deserializeFromFile("saves/" + file + ".save", *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Deserializer GameState Error : "
				  + std::string(ex.what()));
      }
    _tilemap.load(file);
  }

  void			GameState::save(const std::string & file)
  {
    Serializer		s = Serializer::create<JSONSerializer>();
    try
      {
	s->serializeToFile("saves/" + file + ".save", *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Serializer GameState Error : "
				  + std::string(ex.what()));
      }
    _tilemap.save(file);
  }

  void			GameState::pack(ISerializedNode & current) const
  {
    std::list<AEntity*>::const_iterator	it;
    std::list<Player>::const_iterator	itPlayers;
    ISerializedNode*			entityListNode;
    ISerializedNode*			playerListNode;
    int					i;

    entityListNode = current.add("entity");
    for (i = 0, it = _entities.begin(); it != _entities.end(); ++it)
      {
	if ((*it)->expired() == false)
	  {
	    std::stringstream	ss;

	    ss << i;
	    entityListNode->add(ss.str(), *(*it));
	    i++;
	  }
      }
    playerListNode = current.add("players");
  }

  void			GameState::unpack(const ISerializedNode & current)
  {
    ISerializedNode*	entityListNode;
    ISerializedNode*	entityNode;
    EntityFactory	factory;
    AEntity*		entity;
    std::string		type;
    int			size;
    int			index;

    entityListNode = current.get("entity");
    size = entityListNode->size();
    for (index = 0; index < size; index++)
      {
    	std::stringstream	ss;

    	ss << index;
    	entityNode = entityListNode->get(ss.str());
    	entityNode->get("type", type);
    	entity = factory.create(type, *this);
    	if (entity != NULL)
    	  {
    	    entityListNode->get(ss.str(), *entity);
    	    addEntity(entity);
    	  }
    	else
    	  std::cout << "Serializer GameState Warning: unknown entity type" << std::endl;
      }
  }

  void			GameState::initialize()
  {
    Player					*player;
    SerializableVector<glm::ivec2>::iterator	itSpawn;
    int						i;

    if (!this->_skybox.initialize())
      std::cerr << "Error initializing skybox" << std::endl;
    glEnable(GL_CULL_FACE);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);

    std::vector<PlayerConfig>::iterator it;

    for(it = _config->playersConfigs.begin();
    	it != _config->playersConfigs.end(); ++it)
      {
	itSpawn = _tilemap.getSpawns().begin();
	itSpawn += rand() % _tilemap.getSpawns().size();
	player = new Player(*this, *it);
	player->initPosition(itSpawn->x, itSpawn->y);
	std::cout << player->getPosition().x << " " << player->getPosition().x
		  << std::endl;
    	_players.push_back(player);
      }

    // this->save("megaSave1");

    // INIT EN BRUT DES AI
    // for (int i = 0; i != 1; i++)
    //   _AIs.push_back(new AI(*this, glm::vec2(5, 5)));

    // PlayerConfig	playerConfig;
    // playerConfig.inputConfig = new InputConfig;
    // playerConfig.inputConfig->load("inputConfig1.json");
    // playerConfig.splitScreenPosition = glm::vec2(0, 0);
    // playerConfig.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
    // _players.push_back(new Player(*this, playerConfig));

    // PlayerConfig	playerConfig2;
    // playerConfig2.inputConfig = new InputConfig;
    // playerConfig2.inputConfig->load("inputConfig2.json");
    // playerConfig2.splitScreenPosition = glm::vec2(512 * 1.5, 0);
    // playerConfig2.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
    // _players.push_back(new Player(*this, playerConfig2));

    // PlayerConfig	playerConfig3;
    // playerConfig3.inputConfig = new InputConfig;
    // playerConfig3.inputConfig->load("inputConfig3.json");
    // playerConfig3.splitScreenPosition = glm::vec2(0, 384 * 1.5);
    // playerConfig3.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
    // _players.push_back(new Player(*this, playerConfig3));

    // PlayerConfig	playerConfig4;
    // playerConfig4.inputConfig = new InputConfig;
    // playerConfig4.inputConfig->load("inputConfig4.json");
    // playerConfig4.splitScreenPosition = glm::vec2(512 * 1.5, 384 * 1.5);
    // playerConfig4.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
    // _players.push_back(new Player(*this, playerConfig4));

    // addEntity(new BombBonus(glm::vec2(5, 17)));
    // addEntity(new SpeedBonus(glm::vec2(5, 15)));
    // addEntity(new MultiBombBonus(glm::vec2(5, 13)));
    // addEntity(new DarkBonus(glm::vec2(5, 11)));
    // addEntity(new WaterBonus(glm::vec2(5, 9)));
    // addEntity(new PowerBonus(glm::vec2(5, 7)));
    // addEntity(new FireBonus(glm::vec2(5, 5)));
    // addEntity(new RandomBonus(glm::vec2(5, 3)));
    // addEntity(new BoxBonus(glm::vec2(5, 1)));
    // addEntity(new GameBox(glm::vec2(5, 2), *this));
    // addEntity(new GameBox(glm::vec2(5, 4), *this));
    // addEntity(new GameBox(glm::vec2(5, 6), *this));
    // addEntity(new GameBox(glm::vec2(5, 8), *this));
    // addEntity(new GameBox(glm::vec2(5, 10), *this));
    // addEntity(new GameBox(glm::vec2(5, 12), *this));
    // addEntity(new GameBox(glm::vec2(5, 14), *this));
    // addEntity(new GameBox(glm::vec2(5, 16), *this));
    // addEntity(new GameBox(glm::vec2(5, 18), *this));
    // addEntity(new GameBox(glm::vec2(15, 2), *this));
    // addEntity(new GameBox(glm::vec2(15, 3), *this));
    // addEntity(new GameBox(glm::vec2(15, 4), *this));
    // addEntity(new GameBox(glm::vec2(15, 5), *this));
    // addEntity(new GameBox(glm::vec2(15, 6), *this));
    // addEntity(new GameBox(glm::vec2(15, 8), *this));
    // addEntity(new GameBox(glm::vec2(15, 10), *this));
    // addEntity(new GameBox(glm::vec2(15, 12), *this));
    // addEntity(new GameBox(glm::vec2(15, 14), *this));
    // addEntity(new GameBox(glm::vec2(15, 16), *this));
    // addEntity(new GameBox(glm::vec2(15, 18), *this));
  }

  void			GameState::release()
  {
  }

  void			GameState::obscuring()
  {
  }

  void			GameState::revealing()
  {
  }

  void			GameState::draw(float time, Screen& context)
  {
    (void) time;
    Transform		projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
    Transform		cameraSky = Camera(glm::vec3(10, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    PlayerIt		itPlayersCamera;
    RenderState		stateSky(projection, cameraSky);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();
    for (itPlayersCamera = _players.begin(); itPlayersCamera != _players.end(); itPlayersCamera++)
      {
	Player&		currPlayer = *(*itPlayersCamera);
	Transform	camera = Camera(glm::vec3(currPlayer.getPosition().x, currPlayer.getPosition().y - 2, 10),
					glm::vec3(currPlayer.getPosition().x, currPlayer.getPosition().y, 0),
					glm::vec3(0, 0, 1));
	RenderState		state(projection, camera, Transform());

	/// SPLIT SCREEN
	if (_players.size() == 2)
	  {
	    if (std::distance(_players.begin(), itPlayersCamera) == 0)
	      context.split(glm::ivec2(0, 0),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 1)
	      context.split(glm::ivec2(context.getSize().x / 2, context.getSize().y / 2),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	  }
	else if (_players.size() == 3)
	  {
	    if (std::distance(_players.begin(), itPlayersCamera) == 0)
	      context.split(glm::ivec2(0, context.getSize().y / 2),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 1)
	      context.split(glm::ivec2(context.getSize().x / 2, context.getSize().y / 2),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 2)
	      context.split(glm::ivec2(0, 0),
			    glm::ivec2(context.getSize().x, context.getSize().y / 2));
	  }
	else if (_players.size() == 4)
	  {
	    if (std::distance(_players.begin(), itPlayersCamera) == 0)
	      context.split(glm::ivec2(0, context.getSize().y / 2),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 1)
	      context.split(glm::ivec2(context.getSize().x / 2, context.getSize().y / 2),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 2)
	      context.split(glm::ivec2(0, 0),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));

	    if (std::distance(_players.begin(), itPlayersCamera) == 3)
	      context.split(glm::ivec2(context.getSize().x / 2, 0),
			    glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	  }

	context.draw(_tilemap, state);

	//draw entities
	EntitiesIt		entitiesIt;
	for (entitiesIt = _entities.begin(); entitiesIt != _entities.end(); entitiesIt++)
	  if (std::abs((*entitiesIt)->getPosition().x - (*itPlayersCamera)->getPosition().x) < 10 &&
	      std::abs((*entitiesIt)->getPosition().y -(*itPlayersCamera)->getPosition().y) < 10)
	    context.draw(*(*entitiesIt), state);

	//draw players
	PlayerIt	itPlayers;
	for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
	  if (std::abs((*itPlayers)->getPosition().x - (*itPlayersCamera)->getPosition().x) < 12 &&
	      std::abs((*itPlayers)->getPosition().y -(*itPlayersCamera)->getPosition().y) < 10)
	    context.draw(*(*itPlayers), state);

	//draw AI
	// std::list<AI*>::iterator	itAIs;
	// for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
	//   context.draw(*(*itAIs), state);
      }
    context.flush();
  }

  void			GameState::update(float time, const Input& input)
  {
    EntitiesIt it;

    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	_manager.pop();
	PauseState* state = new PauseState(_manager, this);
	_manager.push(state);
 	return;
      }

    // Update all players and AI
    std::list<Player*>::iterator	itPlayers;
    std::list<AI*>::iterator		itAIs;
    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      (*itPlayers)->handleEvents(time, input);
    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      (*itPlayers)->update(time);
    // for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
    //   (*itAIs)->update(time);

    // Update all entities
    for (it = _entities.begin(); it != _entities.end(); it++)
      (*it)->update(time);
    it = _entities.begin();
    while (it != _entities.end())
      {
    	if ((*it)->expired())
    	  it = _entities.erase(it);
    	else
    	  it++;
      }
    _skybox.update();
  }

  void			GameState::addEntity(AEntity* entity)
  {
    _entities.push_back(entity);
  }

  Player&		GameState::getPlayer(unsigned int id)
  {
    std::list<Player*>::iterator	itPlayers;
    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if ((*itPlayers)->getID() == id)
	return (*(*itPlayers));
    throw (std::runtime_error("player not found"));
  }

  std::list<AEntity*>&	GameState::getEntities()
  {
    return (_entities);
  }

  TileMap&		GameState::getTileMap()
  {
    return (_tilemap);
  }
};
