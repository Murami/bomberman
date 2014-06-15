//
// ProjectionPerspective.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:12 2014 otoshigami
// Last update Sun Jun 15 08:31:13 2014 otoshigami
//

#include <glm/gtc/matrix_transform.hpp>
#include "graphic/ProjectionPerspective.hh"

namespace bbm
{
  ProjectionPerspective::ProjectionPerspective(float fov, float ratio, float near, float far)
  {
    _matrix = glm::perspective(fov, ratio, near, far);
  }

  ProjectionPerspective::~ProjectionPerspective()
  {
  }
};
