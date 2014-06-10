//
// MenuBackground.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_2
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun May 11 19:53:03 2014 Manu
// Last update Thu May 15 19:19:10 2014 Manu
//

#ifndef		__MENUBACKGROUND_HH__
# define	__MENUBACKGROUND_HH__

# include	<iostream>
# include	"glm/glm.hpp"
# include	"glm/gtc/matrix_transform.hpp"
# include	"AObject.hh"
# include	"Geometry.hh"
# include	"Texture.hh"

class		MenuBackground : public AObject
{
private :
  gdl::Geometry	_geom;
  gdl::Texture	_tex;

public :
  MenuBackground();
  ~MenuBackground();

public :
  bool		initialize();
  void		update(const gdl::Clock&, gdl::Input&);
  void		draw(gdl::AShader&, const gdl::Clock&);
};

#endif
