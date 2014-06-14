#include <string>
#include "entity/PowerBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  PowerBonus::PowerBonus() : _wall("powerBonus", "default")
  {
  }

  PowerBonus::PowerBonus(const glm::vec2& pos) : _wall("powerBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _used = false;
    _wall.yaw(90);
    _type = "PowerBonus";
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  PowerBonus::~PowerBonus()
  {
  }

  void			PowerBonus::initialize()
  {
    _anim = 0;
    _used = false;
    _wall.yaw(90);
    _type = "PowerBonus";
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  void			PowerBonus::update(float time)
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

  bool			PowerBonus::expired() const
  {
    return (_used);
  }

  void			PowerBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	PowerBonus::getType() const
  {
    return (_type);
  }

  bool			PowerBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			PowerBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (_used == false)
	  {
	    dynamic_cast<APlayer*>(entity)->setTypeBomb(POWER);
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	PowerBonus::getPosition() const
  {
    return (_pos);
  }
};
