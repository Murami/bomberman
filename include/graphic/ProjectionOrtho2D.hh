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
