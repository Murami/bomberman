#ifndef WALL_HH
#define WALL_HH

#include "graphic/IDrawable.hh"
#include "graphic/Object.hh"
#include "graphic/Transformable.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;

  class	Wall : public IDrawable, public Transformable
  {
  public:
    Wall(const std::string& texture, const std::string& shader);
    ~Wall();

  public:
    static void initialize();
    static void release();

  protected:
    void	draw(ARenderer&, const RenderState&);

  private:
    gdl::Texture		*_texture;
    gdl::BasicShader		*_shader;
    static gdl::Geometry       	*_geometry;
  };
};

#endif /* WALL_HH */
