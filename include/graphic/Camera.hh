#ifndef CAMERA_HH
#define CAMERA_HH

#include <glm/glm.hpp>

#include "graphic/Transform.hh"

namespace bbm
{
  class	Camera : public Transform
  {
  public:
    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& vertical);
    Camera(const Camera& camera);
    virtual ~Camera();

    Camera&	operator=(const Camera& camera);

    void	update(const glm::vec3& position, const glm::vec3& target, const glm::vec3& vertical);
  };
};

#endif /* CAMERA_HH */
