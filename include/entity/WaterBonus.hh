#ifndef WATERBONUS_HH
#define WATERBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	WaterBonus : public AEntity
  {
  public:
    WaterBonus();
    WaterBonus(const glm::vec2& pos);
    ~WaterBonus();

    void		update(float time);
    void		initialize();
    void		interact(AEntity *);
    bool		expired() const;
    bool		collide(const glm::vec3&);
    const glm::vec2&	getPosition() const;
    const std::string&	getType() const;

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);


  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* WATERBONUS_HH */
