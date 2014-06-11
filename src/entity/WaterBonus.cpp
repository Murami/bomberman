#include <string>
#include "entity/WaterBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  WaterBonus::WaterBonus() : _wall("waterBonus", "default")
  {

  }

  WaterBonus::WaterBonus(const glm::vec2& pos) : _wall("waterBonus", "default")
  {
    _pos = pos;
    _type = "WaterBonus";
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  WaterBonus::~WaterBonus()
  {
  }

  void          WaterBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void		WaterBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  void		WaterBonus::update(float time)
  {
    (void)time;
  }

  bool		WaterBonus::expired() const
  {
    return (_used);
  }

  void		WaterBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	WaterBonus::getType() const
  {
    return (_type);
  }

  bool			WaterBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			WaterBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  dynamic_cast<Player*>(entity)->setTypeBomb(WATER);
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }
};