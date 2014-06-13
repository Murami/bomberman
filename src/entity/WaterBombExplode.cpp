#include "entity/WaterBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"
#include "sound/SoundManager.hh"

const float	scaleFactor = 1;

namespace bbm
{
  WaterBombExplode::WaterBombExplode(const glm::vec2& position, GameState& gameState) :
    ABombExplode(position, gameState),
    _wall("water", "default")
  {
    SoundManager::getInstance()->play("aquaBomb");
    _type = "WaterBombExplode";
    _wall.setPosition(glm::vec3(_position.x, _position.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  WaterBombExplode::~WaterBombExplode()
  {
  }

  void			WaterBombExplode::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			WaterBombExplode::unpack(const ISerializedNode & current)
  {
    (void)current;
  }

  void			WaterBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
  }

  void			WaterBombExplode::draw(ARenderer& renderer,
					      const RenderState& renderState)
  {
    renderer.draw(_wall, renderState);
  }

  bool			WaterBombExplode::expired() const
  {
    return (_lifespan <= 0);
  }

  void			WaterBombExplode::collideEntity()
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

  const std::string &	WaterBombExplode::getType() const
  {
    return (_type);
  }

  bool			WaterBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
    	pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			WaterBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	dynamic_cast<APlayer*>(entity)->slowSpeed();
      }
  }

};
