//
// Image.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri Jun  6 14:00:02 2014 Manu
// Last update Fri Jun  6 14:08:05 2014 Manu
//

#ifndef		__IMAGE_HH__
# define	__IMAGE_HH__

# include	<iostream>
# include	<string>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"AObject.hh"

namespace	gdl
{
  class		BasicShader;
}

namespace	bbm
{
  class		ARenderer;
  class		RenderState;

  class		Image : public AObject
  {
  private :
    gdl::Geometry	_geom;
    gdl::Texture	_texture;
    const std::string&	_filename;
    gdl::BasicShader*	_shader;

  public :
    bool		initialize();
    void		draw(ARenderer&, const RenderState&);

  public :
    Image(const std::string&);
    ~Image();
  };
}

#endif
