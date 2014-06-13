#include <string>
#include "entity/DarkBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  DarkBonus::DarkBonus() : _wall("darkBonus", "default")
  {
  }

  DarkBonus::DarkBonus(const glm::vec2& pos) : _wall("darkBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _type = "DarkBonus";
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  DarkBonus::~DarkBonus()
  {
  }

  void		DarkBonus::initialize()
  {
    _type = "DarkBonus";
    _anim = 0;
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  void		DarkBonus::update(float time)
  {
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
    (void)time;
  }

  bool		DarkBonus::expired() const
  {
    return (_used);
  }

  void		DarkBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	DarkBonus::getType() const
  {
    return (_type);
  }

  bool			DarkBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			DarkBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (_used == false)
	  {
	    dynamic_cast<APlayer*>(entity)->addScore(100);
	    dynamic_cast<APlayer*>(entity)->setTypeBomb(DARK);
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	DarkBonus::getPosition() const
  {
    return (_pos);
  }
};
