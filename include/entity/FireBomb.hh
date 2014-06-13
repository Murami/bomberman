#ifndef FIREBOMB_HH
#define FIREBOMB_HH

#include "graphic/IDrawable.hh"
#include "graphic/Model.hh"
#include "entity/ABomb.hh"
#include "entity/AEntity.hh"
#include "entity/Player.hh"

namespace bbm
{
  class	ARenderer;
  class	RenderState;
  class	GameState;

  class	FireBomb : public ABomb
  {
  public:
    FireBomb(GameState & GameState);
    FireBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~FireBomb();

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void		initialize();

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    bool		addExplode(float x, float y);

  private:
    float		_anim;
    Model		_model;
  };
};

#endif /* FIREBOMB_HH */
