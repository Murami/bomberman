#include "game/APlayer.hh"
#include "entity/BombFactory.hh"
#include "entity/Player.hh"
#include "entity/BoxBomb.hh"
#include "entity/FireBomb.hh"
#include "entity/PowerBomb.hh"
#include "entity/DarkBomb.hh"
#include "entity/WaterBomb.hh"
#include "entity/MultiBomb.hh"
#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "game/GameState.hh"
#include "sound/SoundManager.hh"
#include "hud/HUD.hh"

const float	maxSpeed = 0.005;
const float	modelScaleFactor = 0.0020;
const float	boxScale = 0.8;
const float	delta = 0.2;//0.8 wtf ?!
const float	deltaTile = 0.2;

namespace bbm
{
  APlayer::APlayer(GameState& gameState) :
    _gameState(gameState)
  {
    _model.setPosition(glm::vec3(12 + 0.5, 12 + 0.5, 0));
    _model.setScale(glm::vec3(modelScaleFactor, modelScaleFactor, modelScaleFactor));
    _model.setRoll(90);
    _move = glm::vec2(0, 0);
    _color = glm::vec4(1, 1, 1, 1);
    _model.setColor(_color);
    _maxBomb = 1;
  }

  APlayer::~APlayer()
  {
  }

  void			APlayer::increaseMaxBomb()
  {
    this->_maxBomb++;
  }

  void			APlayer::setColor(const glm::vec4& color)
  {
    _color = color;
    _model.setColor(_color);
  }

  void			APlayer::pack(ISerializedNode & current) const
  {
    current.add("position", _position);
    current.add("power", _power);
    current.add("nbBombs", _nbBombs);
    current.add("nbBombsBonus", _nbBombsBonus);
    current.add("speed", _speed);
    current.add("alive", _alive);
    current.add("slow", _slow);
    current.add("dark", _dark);
    current.add("typeBomb", _typeBomb);
    current.add("state", _state);
    current.add("score", _score);
    current.add("idPlayer", _idPlayer);
    current.add("id", getID());
    current.add("lastId", getLastID());
    current.add("color", _color);
    current.add("maxBomb", _maxBomb);
    current.add("score", _score);
  }

  void			APlayer::unpack(const ISerializedNode & current)
  {
    int			typeBomb;
    int			state;
    unsigned int	id;
    unsigned int	lastId;

    current.get("position", _position);
    current.get("power", _power);
    current.get("nbBonbs", _nbBombs);
    current.get("nbBombsBonus", _nbBombsBonus);
    current.get("speed", _speed);
    current.get("alive", _alive);
    current.get("slow", _slow);
    current.get("dark", _dark);
    current.get("typeBomb", typeBomb);
    current.get("state", state);
    _typeBomb = static_cast<BombType>(typeBomb);
    _state = static_cast<PlayerState>(state);
    current.get("score", _score);
    current.get("idPlayer", _idPlayer);
    current.get("id", id);
    current.get("lastId", lastId);
    current.get("color", _color);
    current.get("maxBomb", _maxBomb);
    setColor(_color);
    setID(id);
    setLastID(lastId);
    current.get("score", _score);
  }

  void			APlayer::collideMap()
  {
    try
      {
	if (_gameState.getTileMap().collide(_position.x + _move.x + 1 - deltaTile, _position.y  + 1 - deltaTile) ||
	    _gameState.getTileMap().collide(_position.x + _move.x + 1 - deltaTile, _position.y  + deltaTile) ||
	    _gameState.getTileMap().collide(_position.x + _move.x + deltaTile, _position.y  + 1 - deltaTile) ||
	    _gameState.getTileMap().collide(_position.x + _move.x + deltaTile, _position.y  + deltaTile))
	  _move.x = 0;
	if (_gameState.getTileMap().collide(_position.x  + 1 - deltaTile, _position.y + _move.y + 1 - deltaTile) ||
	    _gameState.getTileMap().collide(_position.x  + 1 - deltaTile, _position.y + _move.y + deltaTile) ||
	    _gameState.getTileMap().collide(_position.x  + deltaTile, _position.y + _move.y + 1 - deltaTile) ||
	    _gameState.getTileMap().collide(_position.x  + deltaTile, _position.y + _move.y + deltaTile))
	  _move.y = 0;
      }
    catch (const std::runtime_error &e)
      {
	std::cout << e.what() << std::endl;
	// set spawn;
      }
  }

  void			APlayer::collideEntity()
  {
    std::list<AEntity*>::iterator it;

    for (it = _gameState.getEntities().begin(); it != _gameState.getEntities().end(); it++)
      {
    	if ((*it)->collide(glm::vec3(_position.x + _move.x + 1 - delta, _position.y + _move.y + delta, 0)) ||
    	    (*it)->collide(glm::vec3(_position.x + _move.x + delta, _position.y + _move.y + 1 - delta, 0)) ||
    	    (*it)->collide(glm::vec3(_position.x + _move.x + 1 - delta, _position.y + _move.y + 1 - delta, 0)) ||
    	    (*it)->collide(glm::vec3(_position.x + _move.x + delta, _position.y + _move.y + delta, 0)))
    	  (*it)->interact(this);
      }
  }

  bool				APlayer::collideGameBoxes()
  {
    glm::ivec2			mapsize = _gameState.getMapSize();
    std::vector<AEntity*>	_map = _gameState.getGameBoxes();
    int				posx = _position.x;
    int				posy = _position.y;
    AEntity*			tmp;

    for (int x = -1; x != 2; x++)
      for (int y = -1; y != 2; y++)
	{
	  if (posx + x >= 0 && posy + y >= 0)
	    {
	      tmp = _map[posx + x + (posy + y) * mapsize.x];
	      if (tmp != NULL)
		{
		  if (tmp->collide(glm::vec3(_position.x +_move.x + 1 - delta, _position.y + _move.y + delta, 0)) ||
		      tmp->collide(glm::vec3(_position.x +_move.x + delta, _position.y + _move.y + 1 - delta, 0)) ||
		      tmp->collide(glm::vec3(_position.x +_move.x + 1 - delta, _position.y + _move.y + 1 - delta, 0)) ||
		      tmp->collide(glm::vec3(_position.x +_move.x + delta, _position.y + _move.y + delta, 0)))
		    {
		      tmp->interact(this);
		      return (true);
		    }
		}
	    }
	}
    return (false);
  }

  void			APlayer::manageModel(float time)
  {
    _model.update(time);
    if (_state == IDLE)
      _model.pause();
    else if (_state == DOWN)
      {
	_model.setPitch(0);
	_model.play();
      }
    else if (_state == LEFT)
      {
	_model.setPitch(-90);
	_model.play();
      }
    else if (_state == UP)
      {
	_model.setPitch(180);
	_model.play();
      }
    else if (_state == RIGHT)
      {
	_model.setPitch(90);
	_model.play();
      }
  }

  void			APlayer::managePhysics(float time)
  {
    if (_move.x != 0 && _move.y != 0)
      glm::normalize(_move);
    _move *= _speed * time;
    collideEntity();
    collideGameBoxes();
    collideMap();
    _position += _move;
    _model.setPosition(glm::vec3(_position.x + 0.5, _position.y + 0.5, 0));
  }

  //ATENTION AU REFERENCE VERS LE PLAYER !
  bool			APlayer::expired() const
  {
    return (false);
  }

  bool			APlayer::isDark() const
  {
    return (this->_dark);
  }

  bool			APlayer::isSlow() const
  {
    return (this->_slow);
  }

  BombType		APlayer::getBonusType() const
  {
    return (this->_typeBomb);
  }

  bool			APlayer::isDead() const
  {
    return (_alive);
  }

  void			APlayer::draw(ARenderer& renderer,
				      const RenderState& renderState)
  {
    if (_alive)
      renderer.draw(_model, renderState);
  }

  void			APlayer::interact(AEntity *entity)
  {
    (void) entity;
  }

  bool			APlayer::collide(const glm::vec3& pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
        pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			APlayer::addBombs()
  {
    if (_nbBombs < _maxBomb)
      _nbBombs++;
  }

  int	APlayer::getBomb() const
  {
    return (_nbBombs);
  }

  void			APlayer::addBombsBonus()
  {
    _nbBombsBonus++;
  }

  void			APlayer::addPower()
  {
    _power++;

  }
  void			APlayer::addSpeed()
  {
    if (_slow == true)
      {
	_speed = 0.005;
	_slow = false;
      }
    else
      {
	_speed +=  0.005 / 2;
	if (_speed > maxSpeed)
	  _speed = maxSpeed;
      }
  }

  void			APlayer::setSpeed(float s)
  {
    _speed = s;
    if (_speed > maxSpeed)
      _speed = maxSpeed;
  }

  void			APlayer::slowSpeed()
  {
    if (_slow == false)
      _speed = _speed / 5;
    _slow = true;
  }

  void			APlayer::setDark(bool dark)
  {
    _dark = dark;
  }

  void			APlayer::setPower(int p)
  {
    _power = p;
  }

  float			APlayer::getDelta() const
  {
    return (delta);
  }

  void			APlayer::setMove(const glm::vec2 & mov)
  {
    _move = mov;
  }

  void			APlayer::setTypeBomb(BombType type)
  {
    _typeBomb = type;
  }

  int			APlayer::getPower() const
  {
    return (_power);
  }

  const glm::vec2&	APlayer::getMove() const
  {
    return (_move);
  }

  const glm::vec2&	APlayer::getPosition() const
  {
    return (_position);
  }

  void			APlayer::updateState()
  {
    if (_move.x == 0 && _move.y == 0)
      _state = IDLE;
    else if (_move.y != 0)
      {
	if (_move.y == -1)
	  _state = DOWN;
	else
	  _state = UP;
      }
    else if (_move.y == 0)
      {
	if (_move.x == -1)
	  _state = LEFT;
	else
	  _state = RIGHT;
      }
  }

  void	APlayer::addScore(int score)
  {
    _score += score;
  }

  int	APlayer::getScore() const
  {
    return (_score);
  }

  void	APlayer::die()
  {
    SoundManager::getInstance()->play("scream");
    _alive = false;
  }

};
