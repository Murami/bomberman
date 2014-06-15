#include "entity/FireBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"
#include "sound/SoundManager.hh"

const float	scaleFactor = 1;

namespace bbm
{
  FireBombExplode::FireBombExplode(GameState& gameState) : ABombExplode(gameState), _wall("fire", "default")
  {
    SoundManager::getInstance()->playSound("bomb");
  }

  FireBombExplode::FireBombExplode(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) :
    ABombExplode(position, gameState),
    _wall("fire", "default")
  {
    SoundManager::getInstance()->playSound("bomb");

    _lifespan = 500;
    _idPlayer = idPlayer;
    _type = "FireBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  FireBombExplode::~FireBombExplode()
  {
  }

  void					FireBombExplode::initialize()
  {
    _lifespan = 500;
    _type = "FireBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void					FireBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
    collideGameBoxes();
 }

  void					FireBombExplode::draw(ARenderer& renderer,
							      const RenderState& renderState)
  {
    renderer.draw(_wall, renderState);
  }

  bool					FireBombExplode::expired() const
  {
    return (_lifespan <= 0);
  }

  void					FireBombExplode::collideEntity()
  {
    std::list<AEntity*>::iterator	it;
    float				delta = 0.01;

    for (it = _gameState.getEntities().begin(); it != _gameState.getEntities().end(); it++)
      {
	if (_lifespan != 0 && ((*it)->getType() != getType()) &&
	    ((*it)->collide(glm::vec3(_pos.x + 1 - delta,	_pos.y + delta, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + delta,	_pos.y + 1 - delta, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 0.5,	_pos.y + 0.5, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 1 - delta,	_pos.y + 1 - delta, 0)) ||
	     (*it)->collide(glm::vec3(_pos.x + 1 - delta,	_pos.y + delta, 0))))
	  (*it)->interact(this);
      }
  }

  void					FireBombExplode::collideGameBoxes()
  {
    glm::ivec2				mapsize = _gameState.getMapSize();
    std::vector<AEntity*>		map = _gameState.getGameBoxes();
    AEntity*				tmp;
    float				delta = 0.01;

    tmp = map[_pos.x + _pos.y * mapsize.x];
    if (tmp != NULL)
      {
	if (tmp->collide(glm::vec3(_pos.x + 1 - delta, _pos.y + delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + delta, _pos.y + 1 - delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + 0.5, _pos.y + 0.5, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + 1 - delta, _pos.y + 1 - delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + 1 - delta, _pos.y + delta, 0)))
	  tmp->interact(this);
      }
  }

  const std::string &			FireBombExplode::getType() const
  {
    return (_type);
  }

  bool					FireBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 && pos.x >= _pos.x &&
    	pos.y < _pos.y + 1 && pos.y  >= _pos.y)
      return (true);
    return (false);
  }

  void					FireBombExplode::interact(AEntity * entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (dynamic_cast<APlayer*>(entity)->isDead())
	  {
	    _gameState.getPlayer(_idPlayer).addScore(1000);
	    dynamic_cast<APlayer*>(entity)->die();
	  }
      }
  }

};
