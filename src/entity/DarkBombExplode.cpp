#include "entity/DarkBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"

const float	scaleFactor = 1;

namespace bbm
{
  DarkBombExplode::DarkBombExplode(const glm::vec2& position, GameState& gameState) :
    ABombExplode(position, gameState),
    _wall("dark", "default")
  {
    _type = "DarkBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  DarkBombExplode::~DarkBombExplode()
  {
  }

  void			DarkBombExplode::initialize()
  {
    _type = "DarkBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void			DarkBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
  }

  void			DarkBombExplode::draw(ARenderer& renderer,
					      const RenderState& renderState)
  {
    renderer.draw(_wall, renderState);
  }

  bool			DarkBombExplode::expired() const
  {
    return (_lifespan <= 0);
  }

  void			DarkBombExplode::collideEntity()
  {
    std::list<AEntity*>::iterator it;

    for (it = _gameState.getEntities().begin(); it != _gameState.getEntities().end(); it++)
      {
	if (_lifespan != 0 && ((*it)->getType() != getType()) &&
	    ((*it)->collide(glm::vec3(_pos.x + 1 - 0.01,	_pos.y + 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 0.01,	_pos.y + 1 - 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 0.5,	_pos.y + 0.5, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 1 - 0.01,	_pos.y + 1 - 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 1 - 0.01,	_pos.y + 0.01, 0))))
	  (*it)->interact(this);
      }
  }

  const std::string &	DarkBombExplode::getType() const
  {
    return (_type);
  }

  bool			DarkBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 && pos.x >= _pos.x &&
    	pos.y < _pos.y + 1 && pos.y  >= _pos.y)
      return (true);
    return (false);
  }

  void			DarkBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	dynamic_cast<APlayer*>(entity)->setDark(true);
      }
  }

};
