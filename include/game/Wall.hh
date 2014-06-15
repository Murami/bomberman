//
// Wall.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:38:11 2014 otoshigami
// Last update Sun Jun 15 13:22:24 2014 Manu
//

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
