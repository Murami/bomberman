#ifndef APLAYER_HH
#define APLAYER_HH

#include "entity/Marvin.hh"
#include "entity/AEntity.hh"
#include "events/InputConfig.hh"
#include "events/IEventListener.hh"
#include "graphic/IDrawable.hh"
#include "graphic/Model.hh"
#include "graphic/Transformable.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	Input;
  class RenderState;
  class	ARenderer;
  class	GameState;

  enum PlayerState
    {
      IDLE,
      LEFT,
      RIGHT,
      DOWN,
      UP
    };

  enum BonusType
    {
      NONE,
      SPEED_BONUS,
      BOMB_BONUS,
      POWER_BONUS,
      WATER_BONUS,
      FIRE_BONUS,
      DARK_BONUS,
      BOX_BONUS,
      RANDOM_BONUS,
      MULTIBOMB_BONUS
    };

  enum BombType
    {
      FIRE,
      DARK,
      POWER,
      WATER,
      BOX,
      MULTI,
      RANDOM
    };

  class	APlayer : public AEntity
  {
  public:
    APlayer(GameState& gameState);
    ~APlayer();

    bool		expired() const;
    void		setMove(const glm::vec2 &);
    void		interact(AEntity *);
    bool		collide(const glm::vec3 &);
    const glm::vec2 &	getPosition() const;
    const glm::vec2 &	getMove() const;
    float		getDelta() const;
    int			getPower() const;
    int			getBomb() const;
    void		setTypeBomb(BombType);
    void		setSpeed(float);
    void		setDark(bool);
    void		slowSpeed();
    void		setPower(int);
    bool		isDead() const;
    void		addPower();
    void		addSpeed();
    void		addBombs();
    void		addBombsBonus();
    void		addScore(int score);
    void		die();

    virtual const std::string&	getType() const = 0;
    virtual void		update(float time) = 0;
    virtual void		pack(ISerializedNode & current) const = 0;
    virtual void		unpack(const ISerializedNode & current) = 0;

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  protected:
    void		updateState();
    void		collideMap();
    void		collideEntity();
    void		managePhysics(float time);
    void		manageModel(float time);

  protected:
    glm::vec2		_position; //yes
    glm::vec2		_move; //NO
    int			_power; //yes
    int			_nbBombs; //yes
    int			_nbBombsBonus; //yes
    float      		_speed; //yes
    bool		_alive; //yes
    bool		_slow; //yes
    bool		_dark; //yes
    Marvin		_model; //NO
    BombType		_typeBomb; //yes
    PlayerState		_state; //yes
    GameState&		_gameState; //NO
    int			_score; //yes
  };
};

#endif /* APLAYER_HH */
