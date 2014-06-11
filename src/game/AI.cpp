#include "game/AI.hh"

namespace bbm
{
  // std::vector<ILuaHeir<AI> >::t_MethodPtr>	make_method_list()
  // {
  //   std::vector<ILuaHeir<AI> >::t_MethodPtr>	methods;

  //   methods = {.name = "getPosition", .methodPtr = getPosition};
  //   methods = {.name = "getMove", .methodPtr = getMove};
  //   return (methods);
  // }

  // std::vector<ILuaHeir<AI> >::t_MethodPtr>	AI::_methodPtrs = make_method_list();

  // AI::AI(GameState& gameState, const glm::vec2& position) :
  //   APlayer(gameState)
  // {
  //   _type = "AI";
  //   _position = position;
  // }

  AI::~AI()
  {
  }

  void	AI::update(float time)
  {
    (void) time;
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

  std::string						AI::getClassName() const
  {
    return ("AI");
  }

  // const std::vector<ILuaHeir<AI>::t_MethodPtr>&		AI::getMethodPtr() const
  // {
  //   return (_methodPtrs);
  // }
};
