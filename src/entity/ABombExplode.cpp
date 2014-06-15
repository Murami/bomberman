//
// ABombExplode.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:29:44 2014 quentin desabre
// Last update Sun Jun 15 08:29:45 2014 Desabre Quentin
//

#include "entity/ABombExplode.hh"
#include "game/GameState.hh"
#include "graphic/Utils.hh"

namespace bbm
{
  ABombExplode::ABombExplode(GameState& gameState) : _gameState(gameState)
  {
    _lifespan = 2000;
  }

  ABombExplode::ABombExplode(const glm::vec2 & position, GameState& gameState) : _gameState(gameState)
  {
    _lifespan = 2000;
    _pos.x = snap(position.x);
    _pos.y = snap(position.y);
  }

  ABombExplode::~ABombExplode()
  {

  }

  void			ABombExplode::setLifeSpan(float time)
  {
    _lifespan = time;
  }

  const glm::vec2&	ABombExplode::getPosition() const
  {
    return (_pos);
  }
};
