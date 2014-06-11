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

const float	maxSpeed = 0.01;
const float	modelScaleFactor = 0.0020;
const float	boxScale = 0.8;
const float	delta = 0.8;
const float	deltaTile = 0.2;

namespace bbm
{
  APlayer::APlayer(GameState& gameState) :
    _gameState(gameState)
  {
    _alive = true;
    _slow = false;
    _dark = false;
    _model.setPosition(glm::vec3(12 + 0.5, 12 + 0.5, 0));
    _model.setScale(glm::vec3(modelScaleFactor, modelScaleFactor, modelScaleFactor));
    _model.setRoll(90);
    _position = glm::vec2(12, 12);
    _move = glm::vec2(0, 0);
    _power = 3;
    _typeBomb = FIRE;
    _nbBombs = 1;
    _nbBombsBonus = 1;
    _speed = 0.005;
    _state = IDLE;
  }

  APlayer::~APlayer()
  {
  }

  void			APlayer::pack(ISerializedNode & current) const
  {
    (void) current;
  }

  void			APlayer::unpack(const ISerializedNode & current)
  {
    (void) current;
  }

  void			APlayer::managePhysics(float time)
  {
    _move *= _speed * time;
    collideEntity();
    collideMap();
    _position += _move;
    _model.setPosition(glm::vec3(_position.x + 0.5, _position.y + 0.5, 0));
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

  //ATENTION AU REFERENCE VERS LE PLAYER !
  bool			APlayer::expired() const
  {
    return (false);
  }

  bool			APlayer::isDead() const
  {
    return (_alive);
  }

  void			APlayer::draw(ARenderer& renderer, const RenderState& renderState)
  {
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
    _nbBombs++;
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

  void	APlayer::die()
  {
    _alive = false;
  }

};
