//
// Transform.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:40 2014 otoshigami
// Last update Sun Jun 15 08:31:41 2014 otoshigami
//

#include <glm/gtc/matrix_transform.hpp>
#include "graphic/Transform.hh"

namespace bbm
{
  Transform::Transform()
  {
    _matrix = glm::mat4();
  }

  Transform::Transform(const Transform& transform)
  {
    *this = transform;
  }

  Transform::Transform(const glm::mat4& matrix)
  {
    _matrix = matrix;
  }

  Transform::~Transform()
  {
  }

  Transform&	Transform::operator=(const Transform& transform)
  {
    _matrix = transform._matrix;

    return (*this);
  }

  Transform&	Transform::operator*=(const Transform& transform)
  {
    _matrix *= transform._matrix;

    return (*this);
  }

  Transform	Transform::operator*(const Transform& transform) const
  {
    Transform	result = *this;

    result *= transform;

    return (result);
  }

  void	 Transform::translate(const glm::vec2& translation)
  {
    _matrix = glm::translate(_matrix, glm::vec3(translation.x, translation.y, 0));
  }

  void	 Transform::translate(const glm::vec3& translation)
  {
    _matrix = glm::translate(_matrix, translation);
  }

  void	 Transform::rotate(float angle)
  {
    _matrix = glm::rotate(_matrix, angle, glm::vec3(0, 0, 1));
  }

  void	 Transform::rotate(float angle, const glm::vec3& axis)
  {
    _matrix = glm::rotate(_matrix, angle, axis);
  }

  void	 Transform::scale(const glm::vec2& scaling)
  {
    _matrix = glm::scale(_matrix, glm::vec3(scaling.x, scaling.y, 0));
  }

  void	 Transform::scale(const glm::vec3& scaling)
  {
    _matrix = glm::scale(_matrix, scaling);
  }

  const glm::mat4&	Transform::getMatrix() const
  {
    return (_matrix);
  }
};
