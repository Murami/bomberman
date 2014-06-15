//
// ProjectionOrtho2D.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:07 2014 otoshigami
// Last update Sun Jun 15 08:31:09 2014 otoshigami
//

#include <glm/gtc/matrix_transform.hpp>
#include "graphic/ProjectionOrtho2D.hh"

namespace bbm
{
  ProjectionOrtho2D::ProjectionOrtho2D(float left, float right, float top, float bottom)
  {
    _matrix = glm::ortho(left, right, top, bottom, -1.f, 1.f);
  }

  ProjectionOrtho2D::~ProjectionOrtho2D()
  {
  }
};
