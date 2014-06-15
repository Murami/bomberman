#include "game/AI.hh"
#include "game/GameState.hh"
#include "game/PlayerConfig.hh"

#include "entity/BombFactory.hh"

#include "lua/LuaBiche.hh"
#include "sound/SoundManager.hh"

namespace bbm
{
  void	add_method_to_vector(std::vector<ILuaHeir<AI>::t_MethodPtr>& vect,
			     std::string name, int (AI::*ptr)(lua_State*))
  {
    ILuaHeir<AI>::t_MethodPtr	tmp;

    tmp.name = name;
    tmp.methodPtr = ptr;
    vect.push_back(tmp);
  }

  std::vector<ILuaHeir<AI>::t_MethodPtr>	make_method_list()
  {
    std::vector<ILuaHeir<AI>::t_MethodPtr>	methods;

    add_method_to_vector(methods, "getIdPlayer", &AI::getIdPlayer);
    add_method_to_vector(methods, "goUp", &AI::goUp);
    add_method_to_vector(methods, "goLeft", &AI::goLeft);
    add_method_to_vector(methods, "goRight", &AI::goRight);
    add_method_to_vector(methods, "goDown", &AI::goDown);
    add_method_to_vector(methods, "putBomb", &AI::putBomb);
    add_method_to_vector(methods, "haveBomb", &AI::haveBomb);
    add_method_to_vector(methods, "getBoxes", &AI::getBoxes);
    add_method_to_vector(methods, "getActualDirection", &AI::getActualDirection);
    add_method_to_vector(methods, "setIdle", &AI::setIdle);
    return (methods);
  }

  std::vector<ILuaHeir<AI>::t_MethodPtr>	AI::_methodPtrs = make_method_list();

  AI::AI(GameState& gameState, const PlayerConfig& config) :
    APlayer(gameState)
  {
    _type = "AI";
    _scriptName = "scripts/medium.lua";
    _scriptName = config.IALevel;
    std::cout << "IA level = " << _scriptName << std::endl;
    _position = config.position;
    _power = config.power;
    _nbBombs = config.nbBombs;
    _nbBombsBonus = config.nbBombsBonus;
    _speed = config.speed;
    _alive = config.alive;
    _slow = config.slow;
    _dark = config.dark;
    _typeBomb = config.typeBomb;
    _state = config.state;
    _score = 0;
    if (config.idPlayer)
      _idPlayer = config.idPlayer;
    else
      _idPlayer = getID();
    if (config.id)
      setID(config.id);
    if (config.lastId)
      setLastID(config.lastId);
    _actualDirection = IDLE;
  }

  AI::~AI()
  {
    SoundManager::getInstance()->play("scream");
  }

  void	AI::initialize()
  {

  }

  void	AI::update(float time)
  {
    if (_alive)
      {
	LuaBiche	script(_scriptName);

	script.addObject("player", this);
	script.run();
	updateState();
	managePhysics(time);
	manageModel(time);
      }
  }

  const std::string&	AI::getType() const
  {
    return (_type);
  }

  int	AI::getIdPlayer(lua_State* L)
  {
    lua_pushinteger(L, _idPlayer);
    return (1);
  }

  bool	AI::testCollideMap()
  {
    float	deltaTile = 0.2;

    try
      {
        if (_gameState.getTileMap().collide(_position.x + _move.x + 1 - deltaTile, _position.y  + 1 - deltaTile) ||
            _gameState.getTileMap().collide(_position.x + _move.x + 1 - deltaTile, _position.y  + deltaTile) ||
            _gameState.getTileMap().collide(_position.x + _move.x + deltaTile, _position.y + 1 - deltaTile) ||
            _gameState.getTileMap().collide(_position.x + _move.x + deltaTile, _position.y + deltaTile))
	  return (true);
        if (_gameState.getTileMap().collide(_position.x  + 1 - deltaTile, _position.y + _move.y + 1 - deltaTile) ||
            _gameState.getTileMap().collide(_position.x  + 1 - deltaTile, _position.y + _move.y + deltaTile) ||
            _gameState.getTileMap().collide(_position.x  + deltaTile, _position.y + _move.y + 1 - deltaTile) ||
            _gameState.getTileMap().collide(_position.x  + deltaTile, _position.y + _move.y + deltaTile))
	  return (true);
      }
    catch (const std::runtime_error &e)
      {
	std::cout << e.what() << std::endl;
        // set spawn;
      }
    return (false);
  }


  int	AI::goUp(lua_State*)
  {
    this->setMove(glm::vec2(0, 1));
    _actualDirection = UP;
    return (1);
  }

  int	AI::goLeft(lua_State*)
  {
    this->setMove(glm::vec2(-1, 0));
    _actualDirection = LEFT;
    return (1);
  }

  int	AI::goRight(lua_State*)
  {
    this->setMove(glm::vec2(1, 0));
    _actualDirection = RIGHT;
    return (1);
  }

  int	AI::goDown(lua_State*)
  {
    this->setMove(glm::vec2(0, -1));
    _actualDirection = DOWN;
    return (1);
  }

  int	AI::putBomb(lua_State*)
  {
    if (_nbBombs > 0)
      {
	_nbBombs--;
	_gameState.addEntity(BombFactory::getInstance()->create(FIRE, glm::vec2(_position.x, _position.y), _gameState, getID()));
      }
    return (1);
  }

  int	AI::haveBomb(lua_State* L)
  {
    bool	b = true;

    if (this->getBomb() <= 0)
      b = false;
    lua_pushboolean(L, (int)b);
    return (1);
  }

  int	AI::getActualDirection(lua_State* L)
  {
    lua_pushinteger(L, _actualDirection);
    return (1);
  }

  int	AI::setIdle(lua_State*)
  {
    this->setMove(glm::vec2(0, 0));
    _actualDirection = IDLE;
    return (1);
  }

  int	AI::getBoxes(lua_State* L)
  {
    lua_newtable(L);

    this->setMove(glm::vec2(0, 0.4));
    lua_pushstring(L, "up");
    if (this->collideGameBoxes() || this->testCollideMap())
      lua_pushboolean(L, true);
    else
      lua_pushboolean(L, false);
    lua_rawset(L, -3);

    this->setMove(glm::vec2(-0.4, 0));
    lua_pushstring(L, "left");
    if (this->collideGameBoxes() || this->testCollideMap())
      lua_pushboolean(L, true);
    else
      lua_pushboolean(L, false);
    lua_rawset(L, -3);

    this->setMove(glm::vec2(0.4, 0));
    lua_pushstring(L, "right");
    if (this->collideGameBoxes() || this->testCollideMap())
      lua_pushboolean(L, true);
    else
      lua_pushboolean(L, false);
    lua_rawset(L, -3);

    this->setMove(glm::vec2(0, -0.4));
    lua_pushstring(L, "down");
    if (this->collideGameBoxes() || this->testCollideMap())
      lua_pushboolean(L, true);
    else
      lua_pushboolean(L, false);
    lua_rawset(L, -3);
    return (1);
  }

  std::string						AI::getClassName() const
  {
    return ("AI");
  }

  const std::vector<ILuaHeir<AI>::t_MethodPtr>&		AI::getMethodPtr() const
  {
    return (_methodPtrs);
  }
};
