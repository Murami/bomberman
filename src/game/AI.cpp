#include "game/AI.hh"
#include "lua/LuaBiche.hh"

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
    return (methods);
  }

  std::vector<ILuaHeir<AI>::t_MethodPtr>	AI::_methodPtrs = make_method_list();

  AI::AI(GameState& gameState, const glm::vec2& position) :
    APlayer(gameState), _script("scripts/test.lua")
  {
    _script.addObject("player", this);
    _type = "AI";
    _position = position;
  }

  AI::~AI()
  {
  }

  void	AI::update(float time)
  {
    managePhysics(time);
    manageModel(time);
    _script.run();
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
    std::cout << "up" << std::endl;
    this->setMove(glm::vec2(0, 1));
    return (1);
  }

  int	AI::goLeft(lua_State*)
  {
    std::cout << "left" << std::endl;
    this->setMove(glm::vec2(-1, 0));
    return (1);
  }

  int	AI::goRight(lua_State*)
  {
    std::cout << "right" << std::endl;
    this->setMove(glm::vec2(1, 0));
    return (1);
  }

  int	AI::goDown(lua_State*)
  {
    std::cout << "down" << std::endl;
    this->setMove(glm::vec2(0, -1));
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
