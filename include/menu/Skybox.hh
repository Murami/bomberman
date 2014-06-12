//
// Skybox.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Mon Jun  2 13:10:42 2014 Manu
// Last update Thu Jun 12 11:16:58 2014 Manu
//

#ifndef		__SKYBOX_HH__
# define	__SKYBOX_HH__

# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>
# include	"BasicShader.hh"
# include	"graphic/ShaderManager.hh"
# include	"graphic/IDrawable.hh"
# include	"Texture.hh"
# include	"Geometry.hh"
# include	"graphic/ARenderer.hh"
# include	"FileLoadingException.hh"

namespace	bbm
{
  class		Skybox : public IDrawable
  {
  public :
    static const std::string	VIOLENTDAYS;

  private :
    gdl::Texture       	_texture;
    gdl::Geometry      	_geom;
    gdl::BasicShader*	_shader;
    glm::vec3		_position;
    glm::vec3		_rotation;
    glm::vec3		_scale;

  public :
    void		translate(const glm::vec3&);
    void		rotate(const glm::vec3&, float);
    void		scale(const glm::vec3&);
    glm::mat4		getTransformation();

  protected :
    virtual void	draw(ARenderer&, const RenderState&);

  public :
    bool	initialize();
    void	update();

  public :
    Skybox();
    ~Skybox();
  };
}

#endif
