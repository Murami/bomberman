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

    const glm::vec2&	getPosition() const;

    void		initialize();

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* BOMBBONUS_HH */
