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
