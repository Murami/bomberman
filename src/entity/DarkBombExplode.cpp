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
    _wall.setPosition(glm::vec3(_position.x, _position.y, _position.z));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  DarkBombExplode::~DarkBombExplode()
  {
  }

  void			DarkBombExplode::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			DarkBombExplode::unpack(const ISerializedNode & current)
  {
    (void)current;
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
	    ((*it)->collide(glm::vec3(_position.x + 1 - 0.01,	_position.y + 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_position.x + 0.01,	_position.y + 1 - 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_position.x + 0.5,	_position.y + 0.5, 0)) ||
	     (*it)->collide(glm::vec3(_position.x + 1 - 0.01,	_position.y + 1 - 0.01, 0)) ||
	     (*it)->collide(glm::vec3(_position.x + 1 - 0.01,	_position.y + 0.01, 0))))
	  (*it)->interact(this);
      }
  }

  const std::string &	DarkBombExplode::getType() const
  {
    return (_type);
  }

  bool			DarkBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
    	pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			DarkBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player")
      {
	dynamic_cast<Player *>(entity)->setDark(true);
      }
  }

};
