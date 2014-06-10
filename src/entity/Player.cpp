#include <iostream>
#include <exception>
#include <stdexcept>
#include "entity/BombFactory.hh"
#include "entity/Player.hh"
#include "entity/BoxBomb.hh"
#include "entity/FireBomb.hh"
#include "entity/PowerBomb.hh"
#include "entity/DarkBomb.hh"
#include "entity/WaterBomb.hh"
#include "entity/MultiBomb.hh"
#include "events/Input.hh"
#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "game/GameState.hh"
#include "serializer/ISerializedNode.hh"

//#include "game/PlayerConfig.hh"

const float	maxSpeed = 0.01;
const float	modelScaleFactor = 0.0020;
const float	boxScale = 0.8;
const float	delta = 0.8;
const float	deltaTile = 0.2;

namespace bbm
{
  Player::Player(GameState& gameState, const PlayerConfig& config) :
    _collideBox("fire", "default"),
    _gameState(gameState)
  {
    _playerConfig = config;
    _alive = true;
    _slow = false;
    _dark = false;
    _type = "Player";
    _model.setCurrentAnimation("run", true);
    _model.setPosition(glm::vec3(12 + 0.5, 12 + 0.5, 0));
    _model.setScale(glm::vec3(modelScaleFactor, modelScaleFactor, modelScaleFactor));
    _model.setRoll(90);
    _collideBox.setScale(glm::vec3(boxScale, boxScale, boxScale));
    _collideBox.setPosition(glm::vec3(12, 12, 0));
    _position = glm::vec2(12, 12);
    _move = glm::vec2(0, 0);
    _power = 3;
    _typeBomb = FIRE;
    _nbBombs = 1;
    _nbBombsBonus = 1;
    _speed = 0.005;
    _state = IDLE;
  }

  Player::~Player()
  {
  }

  void			Player::pack(ISerializedNode & current) const
  {

  }

  void			Player::unpack(const ISerializedNode & current)
  {

  }

  void			Player::handleEvents(float time, const Input& input)
  {
    (void) time;
    _move = glm::vec2(0, 0);

    if (input.getKey(_playerConfig.inputConfig->getKey("left")))
      _move += glm::vec2(-1, 0);
    if (input.getKey(_playerConfig.inputConfig->getKey("right")))
      _move += glm::vec2(1, 0);
    if (input.getKey(_playerConfig.inputConfig->getKey("down")))
      _move += glm::vec2(0, -1);
    if (input.getKey(_playerConfig.inputConfig->getKey("up")))
      _move += glm::vec2(0, 1);
    if (input.getKeyDown(_playerConfig.inputConfig->getKey("bomb")))
      {
	if (_nbBombs != 0)
	  {
	    _nbBombs--;
	    _gameState.addEntity(new FireBomb(glm::vec2(_position.x, _position.y), _gameState, getID()));
	  }
      }
    if (input.getKeyDown(_playerConfig.inputConfig->getKey("bomb2")))
      {
	if (_nbBombsBonus != 0 && _typeBomb != FIRE)
	  {
	    if (_typeBomb == RANDOM)
	      _gameState.addEntity(BombFactory::getInstance()->createRandom(glm::vec2(_position.x, _position.y), _gameState, getID()));
	    else
	      _gameState.addEntity(BombFactory::getInstance()->create(_typeBomb, glm::vec2(_position.x, _position.y),
								      _gameState, getID()));
	    _nbBombsBonus--;
	  }
      }
    if (_dark)
      {
	_move.x = -_move.x;
	_move.y = -_move.y;
      }
    updateState();
    if (_move.x != 0 && _move.y != 0)
      glm::normalize(_move);
  }

  void			Player::updateState()
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

  void			Player::managePhysics(float time)
  {
    _move *= _speed * time;
    collideEntity();
    collideMap();
    _position += _move;
    _model.setPosition(glm::vec3(_position.x + 0.5, _position.y + 0.5, 0));
    _collideBox.setPosition(glm::vec3(_position.x, _position.y, 0));
  }

  void			Player::collideMap()
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

  void			Player::collideEntity()
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

  void			Player::manageModel(float time)
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

  void			Player::update(float time)
  {
    managePhysics(time);
    manageModel(time);
  }

  bool			Player::expired() const
  {
    return (_alive);
  }

  void			Player::draw(ARenderer& renderer, const RenderState& renderState)
  {
    renderer.draw(_model, renderState);
    // renderer.draw(_collideBox, renderState);
  }

  void			Player::interact(AEntity *entity)
  {
  }

  bool			Player::collide(const glm::vec3& pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
        pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			Player::addBombs()
  {
    _nbBombs++;
  }

  void			Player::addBombsBonus()
  {
    _nbBombsBonus++;
  }

  void			Player::addPower()
  {
    _power++;

  }
  void			Player::addSpeed()
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

  void			Player::setSpeed(float s)
  {
    _speed = s;
    if (_speed > maxSpeed)
      _speed = maxSpeed;
  }

  void			Player::slowSpeed()
  {
    if (_slow == false)
      _speed = _speed / 5;
    _slow = true;
  }

  void			Player::setDark(bool dark)
  {
    _dark = dark;
  }

  void			Player::setPower(int p)
  {
    _power = p;
  }

  float			Player::getDelta() const
  {
    return (delta);
  }

  void			Player::setMove(const glm::vec2 & mov)
  {
    _move = mov;
  }

  void			Player::setTypeBomb(BombType type)
  {
    _typeBomb = type;
  }

  int			Player::getPower() const
  {
    return (_power);
  }

  const std::string &	Player::getType() const
  {
    return (_type);
  }

  const glm::vec2&	Player::getMove() const
  {
    return (_move);
  }

  const glm::vec2&	Player::getPosition() const
  {
    return (_position);
  }

  const glm::ivec2&	Player::getSplitScreenSize() const
  {
    return (_playerConfig.splitScreenSize);
  }

  const glm::ivec2&	Player::getSplitScreenPosition() const
  {
    return (_playerConfig.splitScreenPosition);
  }
};
