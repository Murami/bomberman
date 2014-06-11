#ifndef AI_HH
#define AI_HH

#include "game/APlayer.hh"
// #include "lua/ILuaHeir.hh"

namespace bbm
{
  class	AI : public APlayer//, public ILuaHeir<AI>
  {
  public:
    AI(GameState& gameState, const glm::vec2& position);
    ~AI();

    void		update(float time);
    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);
    const std::string&	getType() const;

    std::string						getClassName() const;
    // const std::vector<ILuaHeir<AI>::t_MethodPtr>&	getMethodPtr() const;

  private:
    // static std::vector<ILuaHeir<AI> >::t_MethodPtr>	_methodPtrs;
    std::string						_type;
  };
};

#endif /* AI_HH */
