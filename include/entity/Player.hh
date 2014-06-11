#ifndef PLAYER_HH
#define PLAYER_HH

#include "game/APlayer.hh"

namespace bbm
{
  class	Player : public APlayer, public IEventListener
  {
  public:
    Player(GameState& gameState, const PlayerConfig& playerConfig);
    ~Player();

    void		handleEvents(float time, const Input& input);
    void		update(float time);
<<<<<<< HEAD
    bool		expired() const;

    void		setMove(const glm::vec2 &);

  public:
    void		interact(AEntity *);
    bool		collide(const glm::vec3 &);
    const std::string &	getType() const;
    const glm::vec2 &	getPosition() const;
    const glm::vec2 &	getMove() const;
    float		getDelta() const;
    int			getPower() const;
    void		addScore(int);
    bool		isDead() const;
    void		die();
    void		setTypeBomb(BombType);
    void		setSpeed(float);
    void		setDark(bool);
    void		slowSpeed();
    void		setPower(int);
    void		addPower();
    void		addSpeed();
    void		addBombs();
    void		addBombsBonus();
=======
>>>>>>> 0aa5abcd1d36b5a5eb4c111a64a8c63f0c74c83e
    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);
    const std::string&  getType() const;

  private:
    PlayerConfig	_playerConfig;
    std::string		_type;
  };
};

#endif /* PLAYER_HH */
