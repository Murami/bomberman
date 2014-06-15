//
// Camera.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:30:41 2014 otoshigami
// Last update Sun Jun 15 08:30:42 2014 otoshigami
//

#include <glm/gtc/matrix_transform.hpp>
#include "graphic/Camera.hh"

namespace bbm
{
  Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& vertical) :
    Transform()
  {
    this->update(position, target, vertical);
  }

  Camera::Camera(const Camera& camera) :
    Transform()
  {
    *this = camera;
  }

  Camera::~Camera()
  {
  }

  Camera&	Camera::operator=(const Camera& camera)
  {
    _matrix = camera._matrix;

    return (*this);
  }

  void		Camera::update(const glm::vec3& position, const glm::vec3& target, const glm::vec3& vertical)
  {
    _matrix = glm::lookAt(position, target, vertical);
  }
};
