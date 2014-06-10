#include <string>
#include "entity/MultiBombBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

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

  void          MultiBombBonus::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void		MultiBombBonus::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  void		MultiBombBonus::update(float time)
  {
    (void)time;
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
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  dynamic_cast<Player*>(entity)->setTypeBomb(MULTI);
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }
};
