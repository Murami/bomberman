#ifndef BOMBBONUS_HH
#define BOMBBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	BombBonus : public AEntity
  {
  public:
    BombBonus();
    BombBonus(const glm::vec2& pos);
    ~BombBonus();

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void                pack(ISerializedNode & current) const;
    void                unpack(const ISerializedNode & current);


  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    glm::vec2		_pos;
    Wall		_wall;
    bool		_used;
    std::string		_type;
  };
};

#endif /* BOMBBONUS_HH */
