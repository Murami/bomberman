#ifndef AI_HH
#define AI_HH

#include "game/APlayer.hh"
#include "game/PlayerConfig.hh"
#include "lua/ILuaHeir.hh"
#include "lua/LuaBiche.hh"

namespace bbm
{
  class	AI : public APlayer, public ILuaHeir<AI>
  {
  public:
    AI(GameState& gameState, const PlayerConfig& config, std::string scriptName);
    ~AI();

    void		update(float time);
    const std::string&	getType() const;

    int	goUp(lua_State*);
    int	goLeft(lua_State*);
    int	goRight(lua_State*);
    int	goDown(lua_State*);
    int	putBomb(lua_State*);
    int	haveBomb(lua_State*);

    std::string						getClassName() const;
    const std::vector<ILuaHeir<AI>::t_MethodPtr>&	getMethodPtr() const;

  private:
    static std::vector<ILuaHeir<AI>::t_MethodPtr>	_methodPtrs;
    std::string						_type;
    std::string						_scriptName;
  };
};

#endif /* AI_HH */
