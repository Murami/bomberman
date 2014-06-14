#include <iterator>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <SDL.h>
#include "PauseState.hh"
#include "game/Tile.hh"
#include "game/GameState.hh"
#include "game/GameOverState.hh"
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
    // SoundManager::getInstance()->play("bomberTheme");
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
    _mapsize = glm::ivec2(x, y);
    _gameboxes.resize(x * y, NULL);
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
	      addEntity(new GameBox(glm::vec2(posx, posy), 0, *this));
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
    std::list<AI*>::const_iterator	itAIs;
    ISerializedNode*			entityListNode;
    ISerializedNode*			playerListNode;
    ISerializedNode*			AIListNode;
    int					i;

    current.add("mapsize", _mapsize);
    entityListNode = current.add("entity");
    for (i = 0, itEntities = _entities.begin();
	 itEntities != _entities.end(); ++itEntities)
      {
	if ((*itEntities)->expired() == false)
	  {
	    std::stringstream	ss;

	    ss << i;
	    std::cout << "type = " << (*itEntities)->getType() << std::endl;
	    entityListNode->add(ss.str(), *(*itEntities));
	    i++;
	  }
      }
    std::cout << "test1" << std::endl;
    playerListNode = current.add("players");
    for (i = 0, itPlayers = _players.begin();
	 itPlayers != _players.end(); ++itPlayers)
      {
	std::stringstream	ss;

	ss << i;
	playerListNode->add(ss.str(), *(*itPlayers));
	i++;
      }
    std::cout << "test2" << std::endl;
    AIListNode = current.add("AIs");
    for (i = 0, itAIs = _AIs.begin(); itAIs != _AIs.end(); ++itAIs)
      {

	std::stringstream	ss;

	ss << i;
	AIListNode->add(ss.str(), *(*itAIs));
	i++;
      }
    std::cout << "test3" << std::endl;
  }

  void			GameState::unpack(const ISerializedNode & current)
  {

    PlayerConfig	playerConfig;
    ISerializedNode*	entityListNode;
    ISerializedNode*	playersListNode;
    ISerializedNode*	AIListNode;
    ISerializedNode*	entityNode;
    ISerializedNode*	playerNode;
    ISerializedNode*	AINode;
    EntityFactory	factory;
    AEntity*		entity;
    std::string		type;
    int			size;
    int			index;
    int			typeBomb;
    int			state;

    current.get("mapsize", _mapsize);
    _gameboxes.resize(_mapsize.x * _mapsize.y, NULL);
    entityListNode = current.get("entity");
    size = entityListNode->size();
    for (index = 0; index < size; index++)
      {
    	std::stringstream	ss;

    	ss << index;
    	entityNode = entityListNode->get(ss.str());
	std::cout << "index = " << ss.str()<< std::endl;
    	entityNode->get("type", type);
    	entity = factory.create(type, *this);
    	if (entity != NULL)
    	  {
    	    entityListNode->get(ss.str(), *entity);
	    entity->initialize();
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
	playerConfig.inputConfig->load("./input/inputConfig" + ss2.str() + ".json");
	playerNode->get("position", playerConfig.position);
	playerNode->get("power", playerConfig.power);
	playerNode->get("nbBombs", playerConfig.nbBombs);
	playerNode->get("nbBombsBonus", playerConfig.nbBombsBonus);
	playerNode->get("speed", playerConfig.speed);
	playerNode->get("alive", playerConfig.alive);
	playerNode->get("slow", playerConfig.slow);
	playerNode->get("dark", playerConfig.dark);
	playerNode->get("score", playerConfig.score);
	playerNode->get("idPlayer", playerConfig.idPlayer);
	playerNode->get("id", playerConfig.id);
	playerNode->get("lastId", playerConfig.lastId);
	playerNode->get("typeBomb", typeBomb);
	playerNode->get("state", state);
	playerConfig.typeBomb = static_cast<BombType>(typeBomb);
	playerConfig.state = static_cast<PlayerState>(state);
	_config->playersConfigs.push_back(playerConfig);
      }

    AIListNode = current.get("AIs");
    size = AIListNode->size();
    for (index = 0; index < size; index++)
      {

    	std::stringstream	ss;

    	ss << index;
	AINode = AIListNode->get(ss.str());
	playerConfig.inputConfig = NULL;
	AINode->get("position", playerConfig.position);
	AINode->get("power", playerConfig.power);
	AINode->get("nbBombs", playerConfig.nbBombs);
	AINode->get("nbBombsBonus", playerConfig.nbBombsBonus);
	AINode->get("speed", playerConfig.speed);
	AINode->get("alive", playerConfig.alive);
	AINode->get("slow", playerConfig.slow);
	AINode->get("dark", playerConfig.dark);
	AINode->get("score", playerConfig.score);
	AINode->get("idPlayer", playerConfig.idPlayer);
	AINode->get("id", playerConfig.id);
	AINode->get("lastId", playerConfig.lastId);
	AINode->get("typeBomb", typeBomb);
	AINode->get("state", state);
	playerConfig.typeBomb = static_cast<BombType>(typeBomb);
	playerConfig.state = static_cast<PlayerState>(state);
	_config->AIConfigs.push_back(playerConfig);
      }
  }

  void			GameState::initialize()
  {
    SerializableVector<glm::ivec2>::iterator	itSpawn;
    std::vector<glm::vec4>			colors;

    colors.resize(4);
    colors[0] = glm::vec4(0.8, 0.2, 0.2, 1);
    colors[1] = glm::vec4(0.2, 0.8, 0.2, 1);
    colors[2] = glm::vec4(0, 0.4, 1, 1);
    colors[3] = glm::vec4(1, 1, 0.2, 1);

    if (!this->_skybox.initialize())
      std::cerr << "Error initializing skybox" << std::endl;
    glEnable(GL_CULL_FACE);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);

    std::vector<PlayerConfig>::iterator it;

    for(it = _config->playersConfigs.begin();
    	it != _config->playersConfigs.end(); ++it)
      {
	if (_config->load == false)
	  {
	    itSpawn = _tilemap.getSpawns().begin();
	    itSpawn += rand() % _tilemap.getSpawns().size();
	    (*it).position = glm::vec2(itSpawn->x, itSpawn->y);
	  }
	Player*	p = new Player(*this, *it);
	p->setColor(colors[std::distance(_config->playersConfigs.begin(), it)]);
    	_players.push_back(p);
      }
    for(it = _config->AIConfigs.begin();
    	it != _config->AIConfigs.end(); ++it)
      {
	if (_config->load == false)
	  {
	    itSpawn = _tilemap.getSpawns().begin();
	    itSpawn += rand() % _tilemap.getSpawns().size();
	    (*it).position = glm::vec2(itSpawn->x, itSpawn->y);
	  }
	_AIs.push_back(new AI(*this, *it));
      }
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
    Transform		cameraSky = Camera(glm::vec3(10, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    Transform		projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
    PlayerIt		itPlayersCamera;

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();

    for (itPlayersCamera = _players.begin(); itPlayersCamera != _players.end(); itPlayersCamera++)
      {
	Player&			currPlayer = *(*itPlayersCamera);
	Transform		camera = Camera(glm::vec3(currPlayer.getPosition().x, currPlayer.getPosition().y - 2, 10),
						glm::vec3(currPlayer.getPosition().x, currPlayer.getPosition().y, 0),
						glm::vec3(0, 0, 1));
	RenderState		stateSky(projection, cameraSky);
	RenderState		state(projection, camera, Transform());

	splitScreen(context, projection, itPlayersCamera);
	_tilemap.draw(context, state, glm::vec2((*itPlayersCamera)->getPosition().x, (*itPlayersCamera)->getPosition().y));
	drawEntity(context, state, itPlayersCamera);
	drawGameBoxes(context, state, itPlayersCamera);
	drawPlayer(context, state, itPlayersCamera);
	drawAI(context, state);
	glDisable(GL_CULL_FACE);
	context.draw(_skybox, stateSky);
	glEnable(GL_CULL_FACE);
      }
    if (this->_flush)
      context.flush();
  }

  void				GameState::splitScreen(Screen& context, Transform& projection, PlayerIt itPlayersCamera)
  {
    if (_players.size() == 2)
      {
	if (std::distance(_players.begin(), itPlayersCamera) == 0)
	  {
	    context.split(glm::ivec2(0, context.getSize().y / 2),
			  glm::ivec2(context.getSize().x, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / (context.getSize().y / 2), 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 1)
	  {
	    context.split(glm::ivec2(0, 0),
			  glm::ivec2(context.getSize().x, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / (context.getSize().y / 2), 1, 1000);
	  }
      }
    else if (_players.size() == 3)
      {
	if (std::distance(_players.begin(), itPlayersCamera) == 0)
	  {
	    context.split(glm::ivec2(0, context.getSize().y / 2),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 1)
	  {
	    context.split(glm::ivec2(context.getSize().x / 2, context.getSize().y / 2),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 2)
	  {
	    context.split(glm::ivec2(0, 0),
			  glm::ivec2(context.getSize().x, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / (context.getSize().y / 2), 1, 1000);
	  }
      }
    else if (_players.size() == 4)
      {
	if (std::distance(_players.begin(), itPlayersCamera) == 0)
	  {
	    context.split(glm::ivec2(0, context.getSize().y / 2),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 1)
	  {
	    context.split(glm::ivec2(context.getSize().x / 2, context.getSize().y / 2),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 2)
	  {
	    context.split(glm::ivec2(0, 0),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }

	if (std::distance(_players.begin(), itPlayersCamera) == 3)
	  {
	    context.split(glm::ivec2(context.getSize().x / 2, 0),
			  glm::ivec2(context.getSize().x / 2, context.getSize().y / 2));
	    projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 1, 1000);
	  }
      }
  }

  void				GameState::drawEntity(Screen & context, RenderState & state, PlayerIt itPlayersCamera)
  {
    EntitiesIt			entitiesIt;

    for (entitiesIt = _entities.begin(); entitiesIt != _entities.end(); entitiesIt++)
      if (std::abs((*entitiesIt)->getPosition().x - (*itPlayersCamera)->getPosition().x) < 15 &&
	  std::abs((*entitiesIt)->getPosition().y - (*itPlayersCamera)->getPosition().y) < 10)
	context.draw(*(*entitiesIt), state);
  }

  void				GameState::drawAI(Screen & context, RenderState & state)
  {
    std::list<AI*>::iterator	itAIs;

    for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
      context.draw(*(*itAIs), state);
  }

  void				GameState::drawGameBoxes(Screen & context, RenderState & state, PlayerIt itPlayersCamera)
  {
    for (int x = -20; x < 20; x++)
      for (int y = -10; y < 10; y++)
	{
	  int	tx =  (*itPlayersCamera)->getPosition().x;
	  int	ty =  (*itPlayersCamera)->getPosition().y;

	  if (x + tx >= 0 && x + tx < _mapsize.x &&
	      y + ty >= 0 && y + ty < _mapsize.y &&
	      _gameboxes[x + tx + (y + ty) * _mapsize.x] != NULL)
	    {
	      if (_gameboxes[x + tx + (y + ty) * _mapsize.x]->expired() == true)
		_gameboxes[x + tx + (y + ty) *_mapsize.x] = NULL;
	      else
		context.draw(*_gameboxes[x + tx + (y + ty) * _mapsize.x], state);
	    }
	}
  }

  void				GameState::drawPlayer(Screen & context, RenderState & state, PlayerIt itPlayersCamera)
  {
    PlayerIt			itPlayers;

    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if (std::abs((*itPlayers)->getPosition().x - (*itPlayersCamera)->getPosition().x) < 15 &&
	  std::abs((*itPlayers)->getPosition().y -(*itPlayersCamera)->getPosition().y) < 10)
	context.draw(*(*itPlayers), state);
  }

  void			GameState::update(float time, const Input& input)
  {
    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	//_manager.pop();
	PauseState* state = new PauseState(_manager, *this);
	_manager.push(state);
 	return;
      }
    updateAIPlayer(time, input);
    updateEntity(time, input);
    _skybox.update();
  }

  void			GameState::updateAIPlayer(float time, const Input& input)
  {
    std::list<Player*>::iterator	itPlayers;
    std::list<AI*>::iterator		itAIs;
    int					nbPlayer = 0;
    int					nbAi = 0;

    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if ((*itPlayers)->isDead())
	nbPlayer++;
    for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
      if ((*itAIs)->isDead())
	nbAi++;

    // if (nbPlayer == 0 && nbAi == 0)
    //   {
    // 	std::cout << "DRAW" << std::endl;
    // 	_manager.pop();
    // 	_manager.push(new GameOverState(_manager, "draw"));
    //   }
    // else if (nbPlayer == 1 && nbAi == 0)
    //   {
    // 	for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
    // 	  if ((*itPlayers)->isDead())
    // 	    {
    // 	      _manager.pop();
    // 	      _manager.push(new GameOverState(_manager, "player1"));
    // 	      std::cout << "player numero ? won the game with " << (*itPlayers)->getScore() << "points" << std::endl;
    // 	    }
    //   }
    // else if (nbPlayer == 0 && nbAi != 0)
    //   {
    // 	std::cout << "AI won the game !" << std::endl;
    // 	_manager.pop();
    // 	_manager.push(new GameOverState(_manager, "ia"));
    //   }

    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if ((*itPlayers)->isDead())
	(*itPlayers)->handleEvents(time, input);
    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if ((*itPlayers)->isDead())
	(*itPlayers)->update(time);


    for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
      if ((*itAIs)->isDead())
	(*itAIs)->update(time);
  }

  void			GameState::updateEntity(float time, const Input& input)
  {
    EntitiesIt it;

    (void)input;
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
  }


  void			GameState::addEntity(AEntity* entity)
  {
    if (entity->getType() != "GameBox")
      _entities.push_back(entity);
    else
      {
	int	x = entity->getPosition().x;
	int	y = entity->getPosition().y;

	if (x >= 0 && x < _mapsize.x && y >= 0 && y < _mapsize.y)
	  {
	    if (_gameboxes[x + y * _mapsize.x] == NULL)
	      _gameboxes[x + y * _mapsize.x] = entity;
	    else
	      delete (entity);
	  }
      }
  }

  APlayer&		GameState::getPlayer(unsigned int id)
  {
    std::list<Player*>::iterator	itPlayers;
    std::list<AI*>::iterator		itAIs;

    for (itPlayers = _players.begin(); itPlayers != _players.end(); itPlayers++)
      if ((*itPlayers)->getID() == id)
	return (*(*itPlayers));
    for (itAIs = _AIs.begin(); itAIs != _AIs.end(); itAIs++)
      if ((*itAIs)->getID() == id)
	return (*(*itAIs));
    throw (std::runtime_error("player not found"));
  }

  const glm::ivec2&	       	GameState::getMapSize() const
  {
    return (_mapsize);
  }

  std::vector<AEntity*>&	GameState::getGameBoxes()
  {
    return (_gameboxes);
  }

  std::list<Player*>&		GameState::getPlayerList()
  {
    return (_players);
  }

  std::list<AI*>&		GameState::getAIList()
  {
    return (_AIs);
  }

  std::list<AEntity*>&		GameState::getEntities()
  {
    return (_entities);
  }

  TileMap&			GameState::getTileMap()
  {
    return (_tilemap);
  }
};
