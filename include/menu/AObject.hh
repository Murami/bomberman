//
// AObject.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_gdl
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sat May 10 15:42:28 2014 Manu
// Last update Fri Jun  6 14:14:24 2014 Manu
//

#ifndef		__AOBJECT_HH__
# define	__AOBJECT_HH__

# include	<AShader.hh>
# include	<SdlContext.hh>
# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>
# include	<iostream>

class		AObject
{
protected :
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public :
  AObject();
  virtual ~AObject();

// public :
//   virtual bool	initialize() = 0;
//   virtual void	update(const gdl::Clock&, gdl::Input&) = 0;
//   virtual void	draw(gdl::AShader&, const gdl::Clock&) = 0;

public :
  void		translate(const glm::vec3&);
  void		rotate(const glm::vec3&, float);
  void		scale(const glm::vec3&);
  glm::mat4	getTransformation();

};

#endif
