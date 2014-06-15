//
// ProjectionPerspective.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:11 2014 otoshigami
// Last update Sun Jun 15 08:34:12 2014 otoshigami
//

#ifndef PROJECTIONPERSPECTIVE_HH
#define PROJECTIONPERSPECTIVE_HH

#include "graphic/Transform.hh"

namespace bbm
{
  class	ProjectionPerspective : public Transform
  {
  public:
    ProjectionPerspective(float fov, float ratio, float near, float far);
    ~ProjectionPerspective();
  };
};

#endif /* PROJECTIONPERSPECTIVE_HH */
