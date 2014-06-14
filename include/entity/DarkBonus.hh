#ifndef DARKBONUS_HH
#define DARKBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	DarkBonus : public AEntity
  {
  public:
    DarkBonus();
    DarkBonus(const glm::vec2& pos);
    ~DarkBonus();

    void		initialize();
    void		update(float time);
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);
    bool		expired() const;
    const glm::vec2&	getPosition() const;
    const std::string &	getType() const;

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* DARKBONUS_HH */
