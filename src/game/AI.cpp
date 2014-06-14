#include "game/AI.hh"
#include "lua/LuaBiche.hh"
#include "game/GameState.hh"
#include "entity/BombFactory.hh"

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
    add_method_to_vector(methods, "goUpLeft", &AI::goUpLeft);
    add_method_to_vector(methods, "goUpRight", &AI::goUpRight);
    add_method_to_vector(methods, "goDownLeft", &AI::goDownLeft);
    add_method_to_vector(methods, "goDownRight", &AI::goDownRight);
    add_method_to_vector(methods, "putBomb", &AI::putBomb);
    add_method_to_vector(methods, "haveBomb", &AI::haveBomb);
    add_method_to_vector(methods, "getGameBoxes", &AI::getGameBoxes);
    return (methods);
  }

  std::vector<ILuaHeir<AI>::t_MethodPtr>	AI::_methodPtrs = make_method_list();

  AI::AI(GameState& gameState, const PlayerConfig& config) :
    APlayer(gameState)
  {
    _type = "AI";
    _scriptName = "scripts/easy.lua";
    // _scriptName = config.scriptName;
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
  }

  AI::~AI()
  {
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
	managePhysics(time);
	updateState();
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

  int	AI::goUp(lua_State*)
  {
    this->setMove(glm::vec2(0, 1));
    return (1);
  }

  int	AI::goLeft(lua_State*)
  {
    this->setMove(glm::vec2(-1, 0));
    return (1);
  }

  int	AI::goRight(lua_State*)
  {
    this->setMove(glm::vec2(1, 0));
    return (1);
  }

  int	AI::goDown(lua_State*)
  {
    this->setMove(glm::vec2(0, -1));
    return (1);
  }

  int	AI::goUpLeft(lua_State*)
  {
    this->setMove(glm::vec2(-1, 1));
    return (1);
  }

  int	AI::goUpRight(lua_State*)
  {
    this->setMove(glm::vec2(1, 1));
    return (1);
  }

  int	AI::goDownLeft(lua_State*)
  {
    this->setMove(glm::vec2(-1, -1));
    return (1);
  }

  int	AI::goDownRight(lua_State*)
  {
    this->setMove(glm::vec2(1, -1));
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

  int	AI::getGameBoxes(lua_State* L)
  {
    std::vector<AEntity*>		tmp;
    int					mapSize;

    mapSize = _gameState.getMapSize().x;
    tmp = _gameState.getGameBoxes();

    lua_newtable(L);
    lua_pushstring(L, "up");
    lua_pushboolean(L, static_cast<bool>(tmp[_position.x + (_position.y + 1) * mapSize]));
    lua_rawset(L, -3);
    lua_pushstring(L, "left");
    lua_pushboolean(L, static_cast<bool>(tmp[(_position.x - 1) + _position.y * mapSize]));
    lua_rawset(L, -3);
    lua_pushstring(L, "right");
    lua_pushboolean(L, static_cast<bool>(tmp[(_position.x + 1) + _position.y * mapSize]));
    lua_rawset(L, -3);
    lua_pushstring(L, "down");
    lua_pushboolean(L, static_cast<bool>(tmp[_position.x + (_position.y - 1) * mapSize]));
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
