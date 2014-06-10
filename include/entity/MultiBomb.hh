#ifndef MULTIBOMB_HH
#define MULTIBOMB_HH

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

  class	MultiBomb : public ABomb
  {
  public:
    MultiBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~MultiBomb();

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

#endif /* MULTIBOMB_HH */
