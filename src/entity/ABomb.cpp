#include "entity/ABomb.hh"
#include "game/GameState.hh"

namespace bbm
{
  ABomb::ABomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) : _gameState(gameState)
  {
    _anim = 0;
    _used = false;
    _playerIsOver = true;
    _lifespan = 2000;
    _position.x = snap(position.x);
    _position.y = snap(position.y);
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
    return (_position);
  }
}
