#include <glm/gtc/matrix_transform.hpp>
#include "graphic/Transformable.hh"

namespace bbm
{
  Transformable::Transformable() :
    _position(0, 0, 0),
    _scale(1, 1, 1)
  {
    _roll = 0;
    _pitch = 0;
    _yaw = 0;
  }

  Transformable::~Transformable()
  {
  }

  void			Transformable::setPosition(const glm::vec3& translation)
  {
    if (_position != translation)
      {
	_position = translation;
	_transformNeedUpdate = true;
      }
  }

  const glm::vec3&	Transformable::getPosition()
  {
    return (_position);
  }

  void			Transformable::move(const glm::vec3& translation)
  {
    if (translation != glm::vec3(0, 0, 0))
      {
	_position += translation;
	_transformNeedUpdate = true;
      }
  }

  void			Transformable::setScale(const glm::vec3& factor)
  {
    if (_scale != factor)
      {
	_scale = factor;
	_transformNeedUpdate = true;
      }
  }

  const glm::vec3&	Transformable::getScale()
  {
    return (_scale);
  }

  void			Transformable::scale(const glm::vec3& factor)
  {
    if (factor != glm::vec3(1, 1, 1))
      {
	_scale *= factor;
	_transformNeedUpdate = true;
      }
  }

  void			Transformable::setRoll(float angle)
  {
    if (_roll != angle)
      {
	_roll = angle;
	_transformNeedUpdate = true;
      }
  }

  float			Transformable::getRoll()
  {
    return (_roll);
  }

  void			Transformable::roll(float angle)
  {
    if (angle != 0)
      {
	_roll += angle;
	while (_roll > 360)
	  _roll -= 360;
	while (_roll < -360)
	  _roll += 360;
	_transformNeedUpdate = true;
      }
  }

  void			Transformable::setYaw(float angle)
  {
    if (_yaw != angle)
      {
	_yaw = angle;
	_transformNeedUpdate = true;
      }
  }

  float			Transformable::getYaw()
  {
    return (_yaw);
  }

  void			Transformable::yaw(float angle)
  {
    if (angle != 0)
      {
	_yaw += angle;
	while (_yaw > 360)
	  _yaw -= 360;
	while (_yaw < -360)
	  _yaw += 360;
	_transformNeedUpdate = true;
      }
  }

  void			Transformable::setPitch(float angle)
  {
    if (_pitch != angle)
      {
	_pitch = angle;
	_transformNeedUpdate = true;
      }
  }

  float			Transformable::getPitch()
  {
    return (_pitch);
  }

  void			Transformable::pitch(float angle)
  {
    if (angle != 0)
      {
	_pitch += angle;
	while (_pitch > 360)
	  _pitch -= 360;
	while (_pitch < -360)
	  _pitch += 360;
	_transformNeedUpdate = true;
      }
  }

  const Transform&	Transformable::getTransform() const
  {
    if (_transformNeedUpdate)
      {
	glm::mat4	mat;

	mat = glm::translate(mat, _position);
	mat = glm::rotate(mat, _roll,	glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, _pitch,	glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, _yaw,	glm::vec3(0, 0, 1));
	mat = glm::scale(mat, _scale);
	_transform = mat;
	_transformNeedUpdate = false;
      }
    return (_transform);
  }
};
