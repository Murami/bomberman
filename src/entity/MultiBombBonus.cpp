//
// MultiBombBonus.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:28:40 2014 quentin desabre
// Last update Sun Jun 15 20:10:16 2014 Manu
//

#include <string>
#include "entity/MultiBombBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"
#include "sound/SoundManager.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  MultiBombBonus::MultiBombBonus() : _wall("deathBonus", "default")
  {
  }

  MultiBombBonus::MultiBombBonus(const glm::vec2& pos) : _wall("deathBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _type = "MultiBombBonus";
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  MultiBombBonus::~MultiBombBonus()
  {
  }

  void		MultiBombBonus::initialize()
  {
    _type = "MultiBombBonus";
    _anim = 0;
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void		MultiBombBonus::update(float time)
  {
    (void)time;
    if (_anim <= 2)
      {
	_anim += 0.1;
	_wall.move(glm::vec3(0, 0, 0.025));
      }
    else
      {
	_anim += 0.1;
	_wall.move(glm::vec3(0, 0, -0.025));
	if (_anim >= 3.9)
	  _anim = 0;
      }
  }

  bool		MultiBombBonus::expired() const
  {
    return (_used);
  }

  void		MultiBombBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	MultiBombBonus::getType() const
  {
    return (_type);
  }

  bool			MultiBombBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			MultiBombBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (_used == false)
	  {
	    if (SoundManager::getInstance()->soundPlaying())
	      SoundManager::getInstance()->playSound("pick");
	    dynamic_cast<APlayer*>(entity)->setTypeBomb(MULTI);
	    dynamic_cast<APlayer*>(entity)->addScore(100);
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	MultiBombBonus::getPosition() const
  {
    return (_pos);
  }
};
