#include <string>
#include "entity/BoxBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  BoxBonus::BoxBonus() : _wall("boxBonus", "default")
  {

  }

  BoxBonus::BoxBonus(const glm::vec2& pos) : _wall("boxBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _type = "BoxBonus";
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  BoxBonus::~BoxBonus()
  {
  }

  void          BoxBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void		BoxBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  void		BoxBonus::update(float time)
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

  bool		BoxBonus::expired() const
  {
    return (_used);
  }

  void		BoxBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	BoxBonus::getType() const
  {
    return (_type);
  }

  bool			BoxBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			BoxBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  dynamic_cast<Player*>(entity)->setTypeBomb(BOX);
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	BoxBonus::getPosition() const
  {
    return (_pos);
  }
};
