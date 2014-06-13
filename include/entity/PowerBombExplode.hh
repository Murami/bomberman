#ifndef POWERBOMBEXPLODE_HH
#define POWERBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	PowerBombExplode : public ABombExplode
  {
  public:
    PowerBombExplode(GameState & GameState);
    PowerBombExplode(const glm::vec2& position, GameState& gameState, unsigned int id);
    ~PowerBombExplode();

    void			update(float time);
    bool			expired() const;
    const std::string &		getType() const;
    void			interact(AEntity *);
    void			collideEntity();
    void			setLifespan(float);
    bool			collide(const glm::vec3&);

    void		initialize();

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    Wall		       	_wall;
  };
};

#endif /* POWERBOMBEXPLODE_HH */
