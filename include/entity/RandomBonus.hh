#ifndef RANDOMBONUS_HH
#define RANDOMBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	RandomBonus : public AEntity
  {
  public:
    RandomBonus();
    RandomBonus(const glm::vec2& pos);
    ~RandomBonus();

    void		update(float time);
    bool		expired() const;
    void		draw(ARenderer& render, const RenderState& renderState);
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);

  private:
    glm::vec2		_pos;
    Wall		_wall;
    bool		_used;
    std::string		_type;
  };
};

#endif /* RANDOMBONUS_HH */