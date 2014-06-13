#include <string>
#include "entity/Player.hh"
#include "entity/BombBonus.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  BombBonus::BombBonus() : _wall("bombBonus", "default")
  {

  }

  BombBonus::BombBonus(const glm::vec2& pos) : _wall("bombBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _used = false;
    _type = "BombBonus";
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  BombBonus::~BombBonus()
  {
  }

  void			BombBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void			BombBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x + 1 - translate, _pos.y + translate, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void			BombBonus::update(float time)
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
	if (_anim >= 4)
	  _anim = 0;
      }
  }

  bool			BombBonus::expired() const
  {
    return (_used);
  }

  void			BombBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	BombBonus::getType() const
  {
    return (_type);
  }

  bool			BombBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			BombBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  {
	    dynamic_cast<Player*>(entity)->addScore(100);
	    dynamic_cast<Player*>(entity)->addBombs();
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	BombBonus::getPosition() const
  {
    return (_pos);
  }
};
