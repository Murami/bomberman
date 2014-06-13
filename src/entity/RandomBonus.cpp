#include <string>
#include "entity/RandomBonus.hh"
#include "entity/Player.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

const float scaleFactor = 0.8;
const float delta = 1 - 0.8;
const float translate = 0.1;

namespace bbm
{
  RandomBonus::RandomBonus() : _wall("randomBonus", "default")
  {
  }

  RandomBonus::RandomBonus(const glm::vec2& pos) : _wall("randomBonus", "default")
  {
    _anim = 0;
    _pos = pos;
    _type = "RandomBonus";
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }

  RandomBonus::~RandomBonus()
  {
    _type = "RandomBonus";
    _anim = 0;
    _used = false;
    _wall.yaw(90);
    _wall.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    _wall.setPosition(glm::vec3(_pos.x - translate + 1, _pos.y + translate, 0));
  }


  void		RandomBonus::initialize()
  {

  }

  void		RandomBonus::update(float time)
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

  bool		RandomBonus::expired() const
  {
    return (_used);
  }

  void		RandomBonus::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  const std::string &	RandomBonus::getType() const
  {
    return (_type);
  }

  bool			RandomBonus::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta &&
	pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta
	&& pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void			RandomBonus::interact(AEntity *entity)
  {
    if (entity->getType() == "Player")
      {
	if (_used == false)
	  {
	    dynamic_cast<Player*>(entity)->addScore(100);
	    dynamic_cast<Player*>(entity)->setTypeBomb(RANDOM);
	  }
	_used = true;
      }
    if (entity->getType() == "FireBombExplode")
      {
	_used = true;
      }
  }

  const glm::vec2&	RandomBonus::getPosition() const
  {
    return (_pos);
  }
};
