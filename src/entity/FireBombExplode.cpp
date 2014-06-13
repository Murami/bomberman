#include "entity/FireBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"
#include "sound/SoundManager.hh"

const float	scaleFactor = 1;

namespace bbm
{
  FireBombExplode::FireBombExplode(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) :
    ABombExplode(position, gameState),
    _wall("fire", "default")
  {
    SoundManager::getInstance()->play("bomb");

    _idPlayer = idPlayer;
    _type = "FireBombExplode";
    _wall.setPosition(glm::vec3(_position.x, _position.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  FireBombExplode::~FireBombExplode()
  {
  }

  void			FireBombExplode::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			FireBombExplode::unpack(const ISerializedNode & current)
  {
    (void)current;
  }

  void			FireBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
  }

  void			FireBombExplode::draw(ARenderer& renderer,
					      const RenderState& renderState)
  {
    renderer.draw(_wall, renderState);
  }

  bool			FireBombExplode::expired() const
  {
    return (_lifespan <= 0);
  }

  void			FireBombExplode::collideEntity()
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

  const std::string &	FireBombExplode::getType() const
  {
    return (_type);
  }

  bool			FireBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
    	pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			FireBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player")
      {
	if (dynamic_cast<APlayer*>(entity)->isDead())
	  {
	    _gameState.getPlayer(_idPlayer).addScore(1000);
	    dynamic_cast<APlayer*>(entity)->die();
	  }
      }
    if (entity->getType() == "AI")
      {
	if (dynamic_cast<APlayer*>(entity)->isDead())
	  {
	    dynamic_cast<APlayer*>(entity)->die();
	  }
      }
  }

};
