//
// FireBonus.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:30:37 2014 quentin desabre
// Last update Sun Jun 15 08:30:38 2014 Desabre Quentin
//

#include <string>
#include "entity/FireBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  FireBonus::FireBonus() : _wall("fireBonus", "default")
  {
  }

  FireBonus::FireBonus(const glm::vec2& pos) : _wall("fireBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _type = "FireBonus";
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  FireBonus::~FireBonus()
  {
  }

  void		FireBonus::initialize()
  {
    _type = "FireBonus";
    _anim = 0;
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  void		FireBonus::update(float time)
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

  bool		FireBonus::expired() const
  {
    return (_used);
  }

  void		FireBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	FireBonus::getType() const
  {
    return (_type);
  }

  bool			FireBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			FireBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (_used == false)
	  dynamic_cast<APlayer*>(entity)->addPower();
	_used = true;
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	FireBonus::getPosition() const
  {
    return (_pos);
  }
};
