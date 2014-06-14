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
    WaterBombExplode(GameState & GameState);
    WaterBombExplode(const glm::vec2& position, GameState& gameState);
    ~WaterBombExplode();

    void			initialize();
    void			interact(AEntity *);
    void			collideEntity();
    void			collideGameBoxes();
    void			setLifespan(float);
    void			update(float time);
    bool			collide(const glm::vec3&);
    bool			expired() const;
    const std::string &		getType() const;

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    Wall		       	_wall;
  };
};

#endif /* WATERBOMBEXPLODE_HH */
