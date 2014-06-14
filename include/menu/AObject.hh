//
// AObject.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_gdl
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sat May 10 15:42:28 2014 Manu
// Last update Sat Jun 14 17:10:52 2014 Manu
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

public :
  void		translate(const glm::vec3&);
  void		rotate(const glm::vec3&, float);
  void		scale(const glm::vec3&);
  glm::mat4	getTransformation();

public :
  void		setPosition(const glm::vec3&);

};

#endif
