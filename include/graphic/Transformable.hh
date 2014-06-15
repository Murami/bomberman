//
// Transformable.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:32 2014 otoshigami
// Last update Sun Jun 15 08:34:33 2014 otoshigami
//

#ifndef TRANSFORMABLE_HH
#define TRANSFORMABLE_HH

#include <glm/glm.hpp>
#include "graphic/Transform.hh"

namespace bbm
{
  class	Transformable
  {
  private:
    glm::vec3		_position;
    glm::vec3		_scale;
    float		_roll;
    float		_pitch;
    float		_yaw;

    mutable Transform	_transform;
    mutable bool	_transformNeedUpdate;

  public:
    Transformable();
    virtual ~Transformable();

    void		setPosition(const glm::vec3& translation);
    const glm::vec3&	getPosition();
    void		move(const glm::vec3& translation);

    void		setScale(const glm::vec3& factor);
    const glm::vec3&	getScale();
    void		scale(const glm::vec3& factor);

    void		setRoll(float angle);
    float		getRoll();
    void		roll(float angle);

    void		setYaw(float angle);
    float		getYaw();
    void		yaw(float angle);

    void		setPitch(float angle);
    float		getPitch();
    void		pitch(float angle);

    const Transform&	getTransform() const;
  };
};

#endif /* TRANSFORMABLE_HH */
