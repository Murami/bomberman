#ifndef BOXBONUS_HH
#define BOXBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	BoxBonus : public AEntity
  {
  public:
    BoxBonus();
    BoxBonus(const glm::vec2& pos);
    ~BoxBonus();

    void		update(float time);
    bool		expired() const;
    void		draw(ARenderer& render, const RenderState& renderState);
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void		pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);

    const glm::vec2&	getPosition() const;

  private:
    glm::vec2		_pos;
    Wall		_wall;
    bool		_used;
    std::string		_type;
  };
};

#endif /* BOXBONUS_HH */
