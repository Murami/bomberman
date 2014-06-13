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

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);

    const glm::vec2&	getPosition() const;

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    float		_anim;
    glm::vec2		_pos;
    Wall		_wall;
    bool		_used;
    std::string		_type;
  };
};

#endif /* DARKBONUS_HH */
