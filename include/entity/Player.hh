#ifndef PLAYER_HH
#define PLAYER_HH

#include "entity/Marvin.hh"
#include "entity/AEntity.hh"
#include "events/InputConfig.hh"
#include "events/IEventListener.hh"
#include "graphic/IDrawable.hh"
#include "graphic/Model.hh"
#include "graphic/Transformable.hh"
#include "game/Wall.hh"
#include "game/PlayerConfig.hh"

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

  class	Player : public AEntity, public IEventListener
  {
  public:
    Player(GameState& gameState, const PlayerConfig& playerConfig);
    ~Player();

    void		handleEvents(float time, const Input& input);
    void		update(float time);
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
    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);
    const glm::ivec2&	getSplitScreenSize() const;
    const glm::ivec2&	getSplitScreenPosition() const;

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    void		collideMap();
    void		collideEntity();
    void		updateState();
    void		managePhysics(float time);
    void		manageModel(float time);


  private:
    glm::vec2		_position;
    glm::vec2		_move;
    std::string		_type;

    int			_power;
    int			_nbBombs;
    int			_nbBombsBonus;
    float      		_speed;
    bool		_alive;
    int			_score;
    bool		_slow;
    bool		_dark;

    Wall		_collideBox;//A ENLEVER !!
    Marvin		_model;
    BombType		_typeBomb;
    PlayerState		_state;
    PlayerConfig	_playerConfig;
    // InputConfig		_inputConfig;
    GameState&		_gameState;
  };
};

#endif /* PLAYER_HH */
