#ifndef IDRAWABLE_HH
#define IDRAWABLE_HH

#include <map>
#include <string>

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	IDrawable
  {
    friend class ARenderer;

  public:
    virtual ~IDrawable() {}
    static const std::map<std::string, int> primitives;

  protected:
    virtual void	draw(ARenderer& renderer, const RenderState& renderState) = 0;
  };
};

#endif /* IDRAWABLE_HH */
