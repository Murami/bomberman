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
#include "sound/SoundManager.hh"

namespace bbm
{
  GameState::GameState(GameManager& manager,
		       GameStateConfig* config) :
    _tilemap(),
    _manager(manager),
    _config(config)
  {
    SoundManager::getInstance()->play("theme");
    this->_flush = true;
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
    std::list<AEntity*>::const_iterator	itEntities;
    std::list<Player*>::const_iterator	itPlayers;
    ISerializedNode*			entityListNode;
    ISerializedNode*			playerListNode;
    int					i;

    entityListNode = current.add("entity");
    for (i = 0, itEntities = _entities.begin();
	 itEntities != _entities.end(); ++itEntities)
      {
	if ((*itEntities)->expired() == false)
	  {
	    std::stringstream	ss;

	    ss << i;
	    entityListNode->add(ss.str(), *(*itEntities));
	    i++;
	  }
      }
    playerListNode = current.add("players");
    for (i = 0, itPlayers = _players.begin();
	 itPlayers != _players.end(); ++itPlayers)
      {
	std::stringstream	ss;

	ss << i;
	playerListNode->add(ss.str(), *(*itPlayers));
	i++;
      }
  }

  void			GameState::unpack(const ISerializedNode & current)
  {

    PlayerConfig	playerConfig;
    ISerializedNode*	entityListNode;
    ISerializedNode*	playersListNode;
    ISerializedNode*	entityNode;
    ISerializedNode*	playerNode;
    EntityFactory	factory;
    AEntity*		entity;
    std::string		type;
    int			size;
    int			index;
    int			typeBomb;
    int			state;

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
    	  std::cout << "Serializer GameState Warning: unknown entity type"
		    << std::endl;
      }
    playersListNode = current.get("players");
    size = playersListNode->size();
    for (index = 0; index < size; index++)
      {

    	std::stringstream	ss;
	std::stringstream	ss2;

    	ss << index;
	ss2 << index + 1;
	playerNode = playersListNode->get(ss.str());
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load("inputConfig" + ss2.str() + ".json");
	playerNode->get("position", playerConfig.position);
	playerNode->get("power", playerConfig.power);
	playerNode->get("nbBombs", playerConfig.nbBombs);
	playerNode->get("nbBombsBonus", playerConfig.nbBombsBonus);
	playerNode->get("speed", playerConfig.speed);
	playerNode->get("alive", playerConfig.alive);
	playerNode->get("slow", playerConfig.slow);
	playerNode->get("dark", playerConfig.dark);
	playerNode->get("score", playerConfig.score);
	playerNode->get("typeBomb", typeBomb);
	playerNode->get("state", state);
	playerConfig.typeBomb = static_cast<BombType>(typeBomb);
	playerConfig.state = static_cast<PlayerState>(state);
	_config->playersConfigs.push_back(playerConfig);
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
    	_players.push_back(player);
      }

    this->save("megaSave1");

    // INIT EN BRUT DES AI
    // for (int i = 0; i != 1; i++)
    //   _AIs.push_back(new AI(*this, glm::vec2(5, 5)));
  }

  void			GameState::release()
  {
  }

  void			GameState::obscuring()
  {
    _flush = false;
  }

  void			GameState::revealing()
  {
    _flush = true;
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
	  // context.draw(*(*itAIs), state);
      }
    if (this->_flush)
      context.flush();
  }

  void			GameState::update(float time, const Input& input)
  {
    EntitiesIt it;

    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	//_manager.pop();
	PauseState* state = new PauseState(_manager);
	_manager.push(state);
 	return;
      }

    // Update all players and AI
    std::list<Player*>::iterator	itPlayers;
    // std::list<AI*>::iterator		itAIs;
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
