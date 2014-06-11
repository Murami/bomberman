#ifndef SPEEDBONUS_HH
#define SPEEDBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	SpeedBonus : public AEntity
  {
  public:
    SpeedBonus();
    SpeedBonus(const glm::vec2& pos);
    ~SpeedBonus();

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    std::string		_type;
    glm::vec2		_pos;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* SPEEDBONUS_HH */