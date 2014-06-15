//
// Letter.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 13:12:51 2014 Manu
// Last update Sun Jun 15 08:10:08 2014 Manu
//

#include		"LetterManager.hpp"
#include		"Letter.hh"

namespace	bbm
{

  const std::string	Letter::TEXTURE_PATH("./assets/menu/fonts/");
  gdl::Geometry*	Letter::_geom = NULL;

  Letter::Letter(char le, const glm::vec4& color) : _color(color),
						    _position(0, 0, 0),
						    _rotation(0, 0, 0),
						    _scale(1, 1, 1)
  {
    this->_le = le;
  }

  char		Letter::getLe() const
  {
    return (this->_le);
  }

  void		Letter::release()
  {
    delete (_geom);
  }

  void			Letter::create()
  {
    _geom = new gdl::Geometry();
    _geom->setColor(glm::vec4(1, 1, 1, 1));
    _geom->pushVertex(glm::vec3(0, -1, -1));
    _geom->pushVertex(glm::vec3(0, -1, 1));
    _geom->pushVertex(glm::vec3(0, 1, 1));
    _geom->pushVertex(glm::vec3(0, 1, -1));
    _geom->pushUv(glm::vec2(1, 0));
    _geom->pushUv(glm::vec2(0, 0));
    _geom->pushUv(glm::vec2(0, 1));
    _geom->pushUv(glm::vec2(1, 1));
    _geom->build();
  }

  bool		Letter::initialize()
  {
    if (this->_le >= 'A' && this->_le <= 'Z')
      this->_le += 32;
    gdl::Texture* t;
    t = LetterManager::getInstance()->getLetter(this->_le);
    if (!t)
      throw (FileLoadingException(std::string("Error while loading resource for letter ") + this->_le));
    this->_texture = t;
    this->scale(glm::vec3(0.5f, 0.25f, 0.25f));
    this->_shader = ShaderManager::getInstance()->getShader("default");
    return (true);
  }

  void		Letter::translate(const glm::vec3& v)
  {
    this->_position += v;
  }

  void		Letter::rotate(const glm::vec3& axis, float angle)
  {
    this->_rotation += axis * angle;
  }

  void		Letter::scale(const glm::vec3& v)
  {
    this->_scale *= v;
  }

  glm::mat4	Letter::getTransformation()
  {
    glm::mat4	matrix(1);

    matrix = glm::translate(matrix, this->_position);
    matrix = glm::rotate(matrix, this->_rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, this->_rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, this->_rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, this->_scale);
    return (matrix);
  }

  void		Letter::draw(ARenderer& r, const RenderState& state)
  {
    RenderState s(state);

    s.transform = state.transform * this->getTransformation();
    glAlphaFunc(GL_GREATER, 0.9f);
    r.draw(*this->_geom, this->_texture, this->_shader, s, GL_QUADS, this->_color);
  }

  Letter::~Letter()
  {
  }

}
