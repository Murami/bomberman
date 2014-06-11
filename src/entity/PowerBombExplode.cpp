#include "entity/PowerBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"
#include "sound/SoundManager.hh"

const float	scaleFactor = 1;

namespace bbm
{
  PowerBombExplode::PowerBombExplode(const glm::vec2& position, GameState& gameState,
				     unsigned int idPlayer) :
    ABombExplode(position, gameState),
    _wall("fire", "default")
  {
    SoundManager::getInstance()->play("bigBomb");
    _idPlayer = idPlayer;
    _type = "PowerBombExplode";
    _wall.setPosition(glm::vec3(_position.x, _position.y, _position.z));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  PowerBombExplode::~PowerBombExplode()
  {
  }

  void			PowerBombExplode::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			PowerBombExplode::unpack(const ISerializedNode & current)
  {
    (void)current;
  }

  void			PowerBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
  }

  void			PowerBombExplode::draw(ARenderer& renderer,
					      const RenderState& renderState)
  {
    renderer.draw(_wall, renderState);
  }

  bool			PowerBombExplode::expired() const
  {
    return (_lifespan <= 0);
  }

  void			PowerBombExplode::collideEntity()
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

  const std::string &	PowerBombExplode::getType() const
  {
    return (_type);
  }

  bool			PowerBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 && pos.x >= _position.x &&
    	pos.y < _position.y + 1 && pos.y  >= _position.y)
      return (true);
    return (false);
  }

  void			PowerBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player")
      {
	if (dynamic_cast<Player *>(entity)->isDead())
	  {
	    _gameState.getPlayer(_idPlayer).addScore(1000);
	    dynamic_cast<Player *>(entity)->die();
	  }
      }
  }

};
