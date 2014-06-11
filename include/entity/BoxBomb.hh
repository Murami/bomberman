#ifndef BOXBOMB_HH
#define BOXBOMB_HH

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

  class	BoxBomb : public ABomb
  {
  public:
    BoxBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~BoxBomb();

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void                        pack(ISerializedNode & current) const;
    void                        unpack(const ISerializedNode & current);

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    bool		addExplode(float x, float y);

  private:
    Model		_model;
    std::string		_type;
  };
};

#endif /* BOXBOMB_HH */