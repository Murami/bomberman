#include "graphic/ARenderer.hh"
#include "graphic/IDrawable.hh"

namespace bbm
{
  ARenderer::~ARenderer()
  {
  }

  void	ARenderer::draw(IDrawable& drawable, const RenderState& state)
  {
    drawable.draw(*this, state);
  }
};
