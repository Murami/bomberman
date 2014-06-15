//
// ABomb.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:29:59 2014 quentin desabre
// Last update Sun Jun 15 08:30:00 2014 Desabre Quentin
//

#include "entity/ABomb.hh"
#include "game/GameState.hh"

namespace bbm
{
  ABomb::ABomb(GameState& gameState) : _gameState(gameState)
  {
    _anim = 0;
    _used = false;
    _playerIsOver = true;
    _lifespan = 2000;
  }

  ABomb::ABomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) : _gameState(gameState)
  {
    _anim = 0;
    _used = false;
    _playerIsOver = true;
    _lifespan = 2000;
    _pos.x = snap(position.x);
    _pos.y = snap(position.y);
    _idPlayer = idPlayer;
  }

  ABomb::~ABomb()
  {

  }

  void		ABomb::setLifeSpan(float time)
  {
    _lifespan = time;
  }

  const glm::vec2&	ABomb::getPosition() const
  {
    return (_pos);
  }
}
