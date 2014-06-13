#ifndef FIREBOMBEXPLODE_HH
#define FIREBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	FireBombExplode : public ABombExplode
  {
  public:
    FireBombExplode(const glm::vec2& position, GameState& gameState, unsigned int id);
    ~FireBombExplode();

    void			update(float time);
    bool			expired() const;
    const std::string &		getType() const;
    void			interact(AEntity *);
    void			collideEntity();
    void			setLifespan(float);
    bool			collide(const glm::vec3&);

    void			initialize();

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    Wall		       	_wall;
  };
};

#endif /* FIREBOMBEXPLODE_HH */
