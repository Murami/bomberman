//
// ProjectionOrtho2D.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:07 2014 otoshigami
// Last update Sun Jun 15 08:34:08 2014 otoshigami
//

#ifndef PROJECTIONORHTO2D_HH
#define PROJECTIONORTHO2D_HH

#include "graphic/Transform.hh"

namespace bbm
{
  class	ProjectionOrtho2D : public Transform
  {
  public:
    ProjectionOrtho2D(float left, float right, float top, float bottom);
    ~ProjectionOrtho2D();
  };
};

#endif /* PROJECTIONORHTO2D_HH */
