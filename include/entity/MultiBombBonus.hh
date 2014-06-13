#ifndef MULTIBOMBBONUS_HH
#define MULTIBOMBBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	MultiBombBonus : public AEntity
  {
  public:
    MultiBombBonus();
    MultiBombBonus(const glm::vec2& pos);
    ~MultiBombBonus();

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

#endif /* MULTIBOMBBONUS_HH */
