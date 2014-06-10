#ifndef WATERBOMBEXPLODE_HH
#define WATERBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	WaterBombExplode : public ABombExplode
  {
  public:
    WaterBombExplode(const glm::vec2& position, GameState& gameState);
    ~WaterBombExplode();

    void			update(float time);
    bool			expired() const;
    const std::string &		getType() const;
    void			interact(AEntity *);
    void			collideEntity();
    void			setLifespan(float);
    bool			collide(const glm::vec3&);

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    std::string			_type;
    Wall		       	_wall;
  };
};

#endif /* WATERBOMBEXPLODE_HH */
