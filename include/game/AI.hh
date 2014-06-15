#ifndef AI_HH
#define AI_HH

#include "game/APlayer.hh"

#include "lua/ILuaHeir.hh"

namespace bbm
{
  class PlayerConfig;

  class	AI : public APlayer, public ILuaHeir<AI>
  {
  public:
    AI(GameState& gameState, const PlayerConfig& config);
    ~AI();

    void		initialize();
    void		update(float time);
    const std::string&	getType() const;
    bool		testCollideMap();

    int		getIdPlayer(lua_State*);
    int		goUp(lua_State*);
    int		goLeft(lua_State*);
    int		goRight(lua_State*);
    int		goDown(lua_State*);
    int		goUpLeft(lua_State*);
    int		goUpRight(lua_State*);
    int		goDownLeft(lua_State*);
    int		goDownRight(lua_State*);
    int		putBomb(lua_State*);
    int		haveBomb(lua_State*);
    int		getBoxes(lua_State*);
    int		getActualDirection(lua_State*);
    int		setIdle(lua_State*);

    std::string						getClassName() const;
    const std::vector<ILuaHeir<AI>::t_MethodPtr>&	getMethodPtr() const;

  private:
    static std::vector<ILuaHeir<AI>::t_MethodPtr>	_methodPtrs;
    std::string						_type;
    std::string						_scriptName;
    PlayerState						_actualDirection;
  };
};

#endif /* AI_HH */
