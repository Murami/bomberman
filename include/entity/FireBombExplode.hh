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

    void			pack(ISerializedNode & current) const;
    void			unpack(const ISerializedNode & current);

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    unsigned int		_idPlayer;
    std::string			_type;
    Wall		       	_wall;
  };
};

#endif /* FIREBOMBEXPLODE_HH */
