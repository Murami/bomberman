#ifndef PLAYER_HH
#define PLAYER_HH

#include "game/APlayer.hh"
#include "game/PlayerConfig.hh"

namespace bbm
{
  class	Player : public APlayer, public IEventListener
  {
  public:
    Player(GameState& gameState, const PlayerConfig& playerConfig);
    Player(GameState& gameState, const PlayerConfig& playerConfig,
	   glm::vec2 position, int power, int nbBombs, int bBombsBonus,
	   float speed, bool alive, bool slow,bool dark, BombType typeBomb,
	   PlayerState state, int score);
    ~Player();

    void		handleEvents(float time, const Input& input);
    void		update(float time);
    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);
    const std::string&  getType() const;
    void                initPosition(int x, int y);
    PlayerConfig&	getPlayerConfig();

  private:
    PlayerConfig	_playerConfig;
    std::string		_type;
  };
};

#endif /* PLAYER_HH */
