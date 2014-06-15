//
// Transform.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:36 2014 otoshigami
// Last update Sun Jun 15 08:34:37 2014 otoshigami
//

#ifndef TRANSFORM_HH
#define TRANSFORM_HH

#include <glm/glm.hpp>

namespace bbm
{
  class	Transform
  {
  protected:
    glm::mat4	_matrix;

  public:
    Transform();
    Transform(const Transform& transform);
    Transform(const glm::mat4& matrix);
    virtual ~Transform();

    Transform&	operator=(const Transform& transform);
    Transform&	operator*=(const Transform& transform);
    Transform	operator*(const Transform& transform) const;

    void	translate(const glm::vec2& translation);
    void	translate(const glm::vec3& translation);
    void	rotate(float angle);
    void	rotate(float angle, const glm::vec3& axis);
    void	scale(const glm::vec2& scaling);
    void	scale(const glm::vec3& scaling);

    const glm::mat4&	getMatrix() const;
  };
};

#endif /* TRANSFORM _HH */
