#ifndef APLAYER_HH
# define APLAYER_HH

# include "entity/Marvin.hh"
# include "entity/AEntity.hh"
# include "events/InputConfig.hh"
# include "events/IEventListener.hh"
# include "graphic/IDrawable.hh"
# include "graphic/Model.hh"
# include "graphic/Transformable.hh"
# include "game/Wall.hh"
#include "entity/Marvin.hh"
#include "entity/AEntity.hh"

#include "graphic/IDrawable.hh"
#include "graphic/Transformable.hh"
#include "graphic/Model.hh"

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

    void				setColor(const glm::vec4& color);
    int					getScore() const;
    bool				expired() const;
    void				setMove(const glm::vec2 &);
    void				interact(AEntity *);
    bool				collide(const glm::vec3 &);
    const glm::vec2 &			getPosition() const;
    const glm::vec2 &			getMove() const;
    float				getDelta() const;
    int				       	getPower() const;
    int			       		getBomb() const;
    void				setTypeBomb(BombType);
    void				setSpeed(float);
    void				setDark(bool);
    void				slowSpeed();
    void				setPower(int);
    bool				isDead() const;
    void				addPower();
    void				addSpeed();
    void				addBombs();
    void				addBombsBonus();
    void				addScore(int score);
    void				die();
    BombType				getBonusType() const;
    bool				isDark() const;
    bool				isSlow() const;
    void				increaseMaxBomb();

    virtual const std::string&		getType() const = 0;
    virtual void			update(float time) = 0;
    virtual void			initialize() = 0;

  protected:
    void				draw(ARenderer& renderer, const RenderState& renderState);

  protected:
    void				updateState();
    void				collideMap();
    void				collideEntity();
    void				collideGameBoxes();
    void				managePhysics(float time);
    void				manageModel(float time);
    void				pack(ISerializedNode & current) const;
    void				unpack(const ISerializedNode & current);

  protected:
    glm::vec4				_color;
    glm::vec2				_position;
    glm::vec2				_move;
    int				       	_power;
    int				       	_nbBombs;
    int				       	_nbBombsBonus;
    float      				_speed;
    bool				_alive;
    bool				_slow;
    bool				_dark;
    Marvin				_model;
    BombType				_typeBomb;
    PlayerState				_state;
    GameState&				_gameState;
    int					_score;
    int					_maxBomb;
  };
};

#endif /* APLAYER_HH */
