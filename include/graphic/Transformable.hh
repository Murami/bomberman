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
    float		_roll;	//x-axis rotation
    float		_pitch;	//y-axis rotation
    float		_yaw;	//z-axis rotation

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
