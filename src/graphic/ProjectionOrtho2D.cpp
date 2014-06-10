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
