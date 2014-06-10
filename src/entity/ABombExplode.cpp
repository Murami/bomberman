#include "entity/ABombExplode.hh"
#include "game/GameState.hh"
#include "graphic/Utils.hh"

namespace bbm
{
  ABombExplode::ABombExplode(const glm::vec2 & position, GameState& gameState) : _gameState(gameState)
  {
    _lifespan = 2000;
    _position.x = snap(position.x);
    _position.y = snap(position.y);
    _position.z = snap(0.1);
  }

  ABombExplode::~ABombExplode()
  {

  }

  void		ABombExplode::setLifeSpan(float time)
  {
    _lifespan = time;
  }
};
