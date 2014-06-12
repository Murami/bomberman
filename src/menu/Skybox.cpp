//
// Skybox.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Mon Jun  2 13:10:45 2014 Manu
// Last update Thu Jun 12 11:17:57 2014 Manu
//

#include		"graphic/RenderState.hh"
#include		<iostream>
#include		"Skybox.hh"

namespace	bbm
{

  const std::string Skybox::VIOLENTDAYS = "assets/menu/images/violentdays.tga";

  Skybox::Skybox() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
  {
  }

  bool		Skybox::initialize()
  {
    if (!this->_texture.load(VIOLENTDAYS))
      throw (FileLoadingException(std::string("Error while loading ") +
				  VIOLENTDAYS));
    this->_shader = ShaderManager::getInstance()->getShader("default");
    this->_geom.pushVertex(glm::vec3(-10, 10, -10));
    this->_geom.pushVertex(glm::vec3(-10, 10, 10));
    this->_geom.pushVertex(glm::vec3(-10, -10, 10));
    this->_geom.pushVertex(glm::vec3(-10, -10, -10));
    this->_geom.pushUv(glm::vec2(0, 1));
    this->_geom.pushUv(glm::vec2(0.25, 1));
    this->_geom.pushUv(glm::vec2(0.25, 0));
    this->_geom.pushUv(glm::vec2(0, 0));
    this->_geom.pushVertex(glm::vec3(10, 10, -10));
    this->_geom.pushVertex(glm::vec3(10, -10, -10));
    this->_geom.pushVertex(glm::vec3(-10, -10, -10));
    this->_geom.pushVertex(glm::vec3(-10, 10, -10));
    this->_geom.pushUv(glm::vec2(0.75, 1));
    this->_geom.pushUv(glm::vec2(0.75, 0));
    this->_geom.pushUv(glm::vec2(1, 0));
    this->_geom.pushUv(glm::vec2(1, 1));
    this->_geom.pushVertex(glm::vec3(-10, 10, 10));
    this->_geom.pushVertex(glm::vec3(-10, -10, 10));
    this->_geom.pushVertex(glm::vec3(10, -10, 10));
    this->_geom.pushVertex(glm::vec3(10, 10, 10));
    this->_geom.pushUv(glm::vec2(0.25, 1));
    this->_geom.pushUv(glm::vec2(0.25, 0));
    this->_geom.pushUv(glm::vec2(0.5, 0));
    this->_geom.pushUv(glm::vec2(0.5, 1));
    this->_geom.pushVertex(glm::vec3(10, 10, 10));
    this->_geom.pushVertex(glm::vec3(10, -10, 10));
    this->_geom.pushVertex(glm::vec3(10, -10, -10));
    this->_geom.pushVertex(glm::vec3(10, 10, -10));
    this->_geom.pushUv(glm::vec2(0.5, 1));
    this->_geom.pushUv(glm::vec2(0.5, 0));
    this->_geom.pushUv(glm::vec2(0.75, 0));
    this->_geom.pushUv(glm::vec2(0.75, 1));
    this->_geom.build();
    this->scale(glm::vec3(5, 5, 5));
    return (true);
  }

  void		Skybox::translate(const glm::vec3& v)
  {
    this->_position += v;
  }

  void		Skybox::rotate(const glm::vec3& axis, float angle)
  {
    this->_rotation += axis * angle;
  }

  void		Skybox::scale(const glm::vec3& v)
  {
    this->_scale *= v;
  }

  glm::mat4	Skybox::getTransformation()
  {
    glm::mat4	matrix(1);

    matrix = glm::translate(matrix, this->_position);
    matrix = glm::rotate(matrix, this->_rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, this->_rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, this->_rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, this->_scale);
    return (matrix);
  }

  void		Skybox::update()
  {
    this->rotate(glm::vec3(0, 1, 0), 0.1f);
  }

  void		Skybox::draw(ARenderer& r, const RenderState& state)
  {
    RenderState s(state);

    s.transform = state.transform * this->getTransformation();
    r.draw(this->_geom, &this->_texture, this->_shader, s, GL_QUADS);
  }

  Skybox::~Skybox()
  {
  }

}
