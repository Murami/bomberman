//
// Letter.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 13:12:48 2014 Manu
// Last update Fri Jun  6 18:04:55 2014 Manu
//

#ifndef		__LETTER_HH__
# define	__LETTER_HH__

# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>
# include	<string>
# include	"AObject.hh"
# include	"Geometry.hh"
# include	"Texture.hh"
# include	"graphic/ARenderer.hh"
# include	"graphic/RenderState.hh"
# include	"graphic/ShaderManager.hh"

namespace	bbm
{

  class		Letter : public AObject
  {
  public :
    const static	std::string	TEXTURE_PATH;

  private :
    char			_le;
    gdl::Geometry		_geom;
    gdl::Texture		_texture;
    gdl::BasicShader*	_shader;
    const glm::vec4	_color;
    glm::vec3		_position;
    glm::vec3		_rotation;
    glm::vec3		_scale;

  public :
    void		translate(const glm::vec3&);
    void		rotate(const glm::vec3&, float);
    void		scale(const glm::vec3&);
    glm::mat4		getTransformation();

  public :
    void		setColor(const glm::vec4&);

  public :
    bool	initialize();
    void	draw(ARenderer&, const RenderState&);
    char	getLe() const
    {
      return (this->_le);
    }

  public :
    Letter(char, const glm::vec4&);
    ~Letter();
  };
}

#endif
