//
// Frame.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 02:39:57 2014 Manu
// Last update Thu Jun 12 14:12:21 2014 Manu
//

#ifndef		__FRAME_HH__
# define	__FRAME_HH__

# include	<string>
# include	<list>
# include	<iostream>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"graphic/IDrawable.hh"
# include	"glm/glm.hpp"
# include	"glm/gtc/matrix_transform.hpp"
# include	"graphic/ShaderManager.hh"
# include	"FileExplorer.hh"
# include	"Image.hh"
# include	"Letter.hh"
# include	"FileLoadingException.hh"

namespace	gdl
{
  class		BasicShader;
}

namespace	bbm
{
  class		ARenderer;
  class		RenderState;

  class		Frame : public IDrawable
  {
  private :
    gdl::Texture	_texture;
    gdl::Geometry	_geom;
    gdl::BasicShader*	_shader;
    glm::vec3		_position;
    glm::vec3		_rotation;
    glm::vec3		_scale;
    glm::vec4		_color;
    FileExplorer*	_explorer;
    Image*		_icone;
    std::list<Letter*>	_title;

  private :
    void		_createTitle();
    void		_createIcone();

  public :
    void		translate(const glm::vec3&);
    void		rotate(const glm::vec3&, float);
    void		scale(const glm::vec3&);
    glm::mat4		getTransformation();

  public :
    bool		initialize();

  public :
    virtual void	draw(ARenderer&, const RenderState&);

  public :
    void		nextSave();
    void		prevSave();
    FileExplorer*	getExplorer();

  public :
    Frame(const glm::vec4& color);
    ~Frame();
  };
}

#endif
