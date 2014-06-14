#ifndef BOMBBOMB_HH
#define BOMBBOMB_HH

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

  class	WaterBomb : public ABomb
  {
  public:
    WaterBomb(GameState & GameState);
    WaterBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~WaterBomb();

    void		initialize();
    void		update(float time);
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);
    bool		expired() const;
    const std::string &	getType() const;

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    bool		addExplode(float x, float y);

  private:
    Model		_model;
  };
};

#endif /* BOMBBOMB_HH */
