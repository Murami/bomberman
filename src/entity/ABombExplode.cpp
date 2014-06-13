#include "entity/ABombExplode.hh"
#include "game/GameState.hh"
#include "graphic/Utils.hh"

namespace bbm
{
  ABombExplode::ABombExplode(const glm::vec2 & position, GameState& gameState) : _gameState(gameState)
  {
    _lifespan = 2000;
    _pos.x = snap(position.x);
    _pos.y = snap(position.y);
  }

  ABombExplode::~ABombExplode()
  {

  }

  void		ABombExplode::setLifeSpan(float time)
  {
    _lifespan = time;
  }

  const glm::vec2&	ABombExplode::getPosition() const
  {
    return (_pos);
  }
};
