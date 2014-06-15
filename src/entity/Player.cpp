//
// Player.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:28:32 2014 quentin desabre
// Last update Sun Jun 15 08:28:33 2014 Desabre Quentin
//

#include <iostream>
#include <exception>
#include <stdexcept>

#include "events/Input.hh"
#include "events/InputConfig.hh"

#include "game/GameState.hh"
#include "game/PlayerConfig.hh"

#include "entity/BombFactory.hh"

const float	maxSpeed = 0.005;
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
    _scriptName = "";
    if (config.idPlayer)
      _idPlayer = config.idPlayer;
    else
      _idPlayer = getID();
    if (config.id)
      setID(config.id);
    if (config.lastId)
      setLastID(config.lastId);
  }

  Player::~Player()
  {
  }

  void			Player::initialize()
  {
  }

  PlayerConfig&		Player::getPlayerConfig()
  {
    return (this->_playerConfig);
  }

  void			Player::update(float time)
  {
    if (_alive)
      {
	updateState();
	if (_move.x != 0 && _move.y != 0)
	  glm::normalize(_move);
	managePhysics(time);
	manageModel(time);
      }
  }

  void			Player::handleEvents(float time, const Input& input)
  {
    (void) time;
    _move = glm::vec2(0, 0);

    if (input.getKey(_playerConfig.inputConfig->getKey("left")) ||
	input.getButton(Joystick::LEFT, _playerConfig.idGamepad - 1))
      _move += glm::vec2(-1, 0);
    if (input.getKey(_playerConfig.inputConfig->getKey("right")) ||
	input.getButton(Joystick::RIGHT, _playerConfig.idGamepad - 1))
      _move += glm::vec2(1, 0);
    if (input.getKey(_playerConfig.inputConfig->getKey("down")) ||
	input.getButton(Joystick::DOWN, _playerConfig.idGamepad - 1))
      _move += glm::vec2(0, -1);
    if (input.getKey(_playerConfig.inputConfig->getKey("up")) ||
	input.getButton(Joystick::UP, _playerConfig.idGamepad - 1))
      _move += glm::vec2(0, 1);
    if (input.getKeyDown(_playerConfig.inputConfig->getKey("bomb")) ||
	input.getButtonDown(Joystick::CROSS, _playerConfig.idGamepad - 1))
      {
	if (_nbBombs != 0)
	  {
	    _nbBombs--;
	    _gameState.addEntity(BombFactory::getInstance()->create(FIRE, glm::vec2(_position.x, _position.y),
								    _gameState, getID()));
	  }
      }
    if (input.getKeyDown(_playerConfig.inputConfig->getKey("bomb2")) ||
	input.getButtonDown(Joystick::CIRCLE, _playerConfig.idGamepad - 1))
      {
	if (_nbBombsBonus != 0 && _typeBomb != FIRE)
	  {
	    if (_typeBomb == RANDOM)
	      _gameState.addEntity(BombFactory::getInstance()->createRandom(glm::vec2(_position.x, _position.y),
									    _gameState, getID()));
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
