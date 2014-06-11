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
    _pos = pos;
    _type = "SpeedBonus";
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
  }

  SpeedBonus::~SpeedBonus()
  {
  }

  void			SpeedBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void			SpeedBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
  }

  void			SpeedBonus::update(float time)
  {
    (void)time;
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
    if (entity->getType() == "Player")
      {
	if (!_used)
	  {
	    dynamic_cast<Player*>(entity)->addScore(100);
	    dynamic_cast<Player*>(entity)->addSpeed();
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }

};
