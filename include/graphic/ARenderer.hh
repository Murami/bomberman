#ifndef ARENDERER_HH
#define ARENDERER_HH

#include <Texture.hh>
#include <BasicShader.hh>
#include <Geometry.hh>
#include <Model.hh>

namespace bbm
{
  class IDrawable;
  class	RenderState;

  class	ARenderer
  {
  public:
    virtual ~ARenderer();

    void		draw(IDrawable& drawable, const RenderState& state);
    virtual void	draw(gdl::Geometry& geometry, gdl::Texture* texture, gdl::BasicShader* shader, const RenderState& state, int primitive) = 0;
    virtual void	draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& state, float time) = 0;
  };
};

#endif /* ARENDERER_HH */
