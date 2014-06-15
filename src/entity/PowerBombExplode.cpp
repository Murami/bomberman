//
// PowerBombExplode.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:28:13 2014 quentin desabre
// Last update Sun Jun 15 13:17:16 2014 Manu
//

#include "entity/PowerBombExplode.hh"
#include "graphic/Utils.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"

const float	scaleFactor = 1;

namespace bbm
{
  PowerBombExplode::PowerBombExplode(GameState& gameState) : ABombExplode(gameState), _wall("fire2", "default")
  {
  }

  PowerBombExplode::PowerBombExplode(const glm::vec2& position, GameState& gameState,
				     unsigned int idPlayer) :
    ABombExplode(position, gameState),
    _wall("fire2", "default")
  {
    _lifespan = 500;
    _idPlayer = idPlayer;
    _type = "PowerBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  PowerBombExplode::~PowerBombExplode()
  {
  }

  void			PowerBombExplode::initialize()
  {
    _lifespan = 500;
    _type = "PowerBombExplode";
    _wall.setPosition(glm::vec3(_pos.x, _pos.y, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void			PowerBombExplode::update(float time)
  {
    _lifespan -= time;
    collideEntity();
    collideGameBoxes();
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

  void				PowerBombExplode::collideGameBoxes()
  {
    glm::ivec2				mapsize = _gameState.getMapSize();
    std::vector<AEntity*>&		map = _gameState.getGameBoxes();
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

  void			PowerBombExplode::collideEntity()
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

  const std::string &	PowerBombExplode::getType() const
  {
    return (_type);
  }

  bool			PowerBombExplode::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 && pos.x >= _pos.x &&
    	pos.y < _pos.y + 1 && pos.y  >= _pos.y)
      return (true);
    return (false);
  }

  void			PowerBombExplode::interact(AEntity * entity)
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
