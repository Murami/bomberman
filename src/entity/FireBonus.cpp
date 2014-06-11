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
    _pos = pos;
    _type = "FireBonus";
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  FireBonus::~FireBonus()
  {
  }

  void          FireBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void		FireBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x + translate, _pos.y + translate, 0));
  }

  void		FireBonus::update(float time)
  {
    (void)time;
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
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  dynamic_cast<Player*>(entity)->addPower();
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }
};