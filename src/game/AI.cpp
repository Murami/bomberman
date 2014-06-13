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

    add_method_to_vector(methods, "goUp", &AI::goUp);
    add_method_to_vector(methods, "goLeft", &AI::goLeft);
    add_method_to_vector(methods, "goRight", &AI::goRight);
    add_method_to_vector(methods, "goDown", &AI::goDown);
    add_method_to_vector(methods, "putBomb", &AI::putBomb);
    add_method_to_vector(methods, "haveBomb", &AI::haveBomb);
    return (methods);
  }

  std::vector<ILuaHeir<AI>::t_MethodPtr>	AI::_methodPtrs = make_method_list();

  AI::AI(GameState& gameState, const glm::vec2& position) :
    APlayer(gameState)
  {
    _type = "AI";
    _position = position;
    // this->initialize();
  }

  AI::~AI()
  {
  }

  void	AI::initialize()
  {
    _script = new LuaBiche("scripts/easy.lua");
    _script->addObject("player", this);
  }

  void	AI::update(float time)
  {
    LuaBiche	tmp("scripts/easy.lua");

    tmp.addObject("player", this);
    tmp.run();
    managePhysics(time);
    updateState();
    manageModel(time);
  }

  void  AI::pack(ISerializedNode & current) const
  {
    (void) current;
  }

  void  AI::unpack(const ISerializedNode & current)
  {
    (void) current;
  }

  const std::string&	AI::getType() const
  {
    return (_type);
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

  int	AI::putBomb(lua_State*)
  {
    _nbBombs--;
    _gameState.addEntity(BombFactory::getInstance()->create(FIRE, glm::vec2(_position.x, _position.y), _gameState, getID()));
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

  std::string						AI::getClassName() const
  {
    return ("AI");
  }

  const std::vector<ILuaHeir<AI>::t_MethodPtr>&		AI::getMethodPtr() const
  {
    return (_methodPtrs);
  }
};
