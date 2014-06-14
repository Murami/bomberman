#ifndef FIREBONUS_HH
#define FIREBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	FireBonus : public AEntity
  {
  public:
    FireBonus();
    FireBonus(const glm::vec2& pos);
    ~FireBonus();

    void		initialize();
    void		update(float time);
    void		interact(AEntity *);
    bool		expired() const;
    bool		collide(const glm::vec3&);
    const std::string &	getType() const;
    const glm::vec2&	getPosition() const;

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* FIREBONUS_HH */
