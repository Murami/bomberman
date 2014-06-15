//
// SpeedBonus.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:31:11 2014 quentin desabre
// Last update Sun Jun 15 08:31:12 2014 Desabre Quentin
//

#include <string>
#include "entity/Player.hh"
#include "entity/SpeedBonus.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  SpeedBonus::SpeedBonus() : _wall("speedBonus", "default")
  {
  }

  SpeedBonus::SpeedBonus(const glm::vec2& pos) : _wall("speedBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _used = false;
    _wall.yaw(90);
    _type = "SpeedBonus";
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
  }

  SpeedBonus::~SpeedBonus()
  {
  }

  void			SpeedBonus::initialize()
  {
    _anim = 0;
    _used = false;
    _wall.yaw(90);
    _type = "SpeedBonus";
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
  }

  void			SpeedBonus::update(float time)
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

  bool			SpeedBonus::expired() const
  {
    return (_used);
  }

  void			SpeedBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	SpeedBonus::getType() const
  {
    return (_type);
  }

  bool			SpeedBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			SpeedBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (!_used)
	  {
	    dynamic_cast<APlayer*>(entity)->addScore(100);
	    dynamic_cast<APlayer*>(entity)->addSpeed();
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	SpeedBonus::getPosition() const
  {
    return (_pos);
  }
};
