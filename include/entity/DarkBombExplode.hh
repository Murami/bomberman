#ifndef DARKBOMBEXPLODE_HH
#define DARKBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	DarkBombExplode : public ABombExplode
  {
  public:
    DarkBombExplode(const glm::vec2& position, GameState& gameState);
    ~DarkBombExplode();

    void			update(float time);
    bool			expired() const;
    const std::string &		getType() const;
    void			interact(AEntity *);
    void			collideEntity();
    void			setLifespan(float);
    bool			collide(const glm::vec3&);

    void                        pack(ISerializedNode & current) const;
    void                        unpack(const ISerializedNode & current);

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    std::string			_type;
    Wall		       	_wall;
  };
};

#endif /* DARKBOMBEXPLODE_HH */
