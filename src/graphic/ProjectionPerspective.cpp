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
