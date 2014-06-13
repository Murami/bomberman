#include <iostream>
#include <exception>
#include <stdexcept>
#include "events/Input.hh"
#include "game/GameState.hh"
#include "entity/BombFactory.hh"

const float	maxSpeed = 0.01;
const float	modelScaleFactor = 0.0020;
const float	boxScale = 0.8;
const float	delta = 0.8;
const float	deltaTile = 0.2;

namespace bbm
{
  Player::Player(GameState& gameState, const PlayerConfig& config) :
    APlayer(gameState)
  {
    _playerConfig = config;
    _type = "Player";
    _position = config.position;
    _power = config.power;
    _nbBombs = config.nbBombs;
    _nbBombsBonus = config.nbBombsBonus;
    _speed = config.speed;
    _alive = config.alive;
    _slow = config.slow;
    _dark = config.dark;
    _typeBomb = config.typeBomb;
    _state = config.state;
    _score = config.score;
  }

  Player::~Player()
  {
  }

  PlayerConfig&		Player::getPlayerConfig()
  {
    return (this->_playerConfig);
  }

  void			Player::pack(ISerializedNode & current) const
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
  }

  void			Player::unpack(const ISerializedNode & current)
  {
    int			typeBomb;
    int			state;

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
  }

  void			Player::update(float time)
  {
    updateState();
    if (_move.x != 0 && _move.y != 0)
      glm::normalize(_move);
    managePhysics(time);
    manageModel(time);
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
	    _gameState.addEntity(BombFactory::getInstance()->create(FIRE, glm::vec2(_position.x, _position.y), _gameState, getID()));
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
  }

  const std::string&	Player::getType() const
  {
    return (_type);
  }

  void			Player::initPosition(int x, int y)
  {
    _position = glm::vec2(x, y);
  }
};
