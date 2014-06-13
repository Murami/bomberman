#ifndef POWERBONUS_HH
#define POWERBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	PowerBonus : public AEntity
  {
  public:
    PowerBonus();
    PowerBonus(const glm::vec2& pos);
    ~PowerBonus();

    void		update(float time);
    bool		expired() const;
    void		draw(ARenderer& render, const RenderState& renderState);
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    const glm::vec2&	getPosition() const;

    void		initialize();

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* POWERBONUS_HH */
