//
// Image.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri Jun  6 14:00:05 2014 Manu
// Last update Thu Jun 12 12:11:19 2014 Manu
//

#include		"graphic/ARenderer.hh"
#include		"graphic/RenderState.hh"
#include		"Image.hh"
#include		"graphic/ShaderManager.hh"

namespace		bbm
{

  Image::Image(const std::string& filename) : AObject(),
					      _filename(filename)
  {
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  bool		Image::initialize()
  {
    this->_shader = ShaderManager::getInstance()->getShader("default");
    if (!this->_texture.load(this->_filename))
      {
	std::cerr << "Image : unable to load " << this->_filename << std::endl;
	return (false);
      }
    this->_geom.setColor(glm::vec4(1, 1, 1, 1));
    this->_geom.pushVertex(glm::vec3(0, -1, -1));
    this->_geom.pushVertex(glm::vec3(0, -1, 1));
    this->_geom.pushVertex(glm::vec3(0, 1, 1));
    this->_geom.pushVertex(glm::vec3(0, 1, -1));
    this->_geom.pushUv(glm::vec2(0, 0));
    this->_geom.pushUv(glm::vec2(1, 0));
    this->_geom.pushUv(glm::vec2(1, 1));
    this->_geom.pushUv(glm::vec2(0, 1));
    this->_geom.build();
    return (true);
  }

  void		Image::draw(ARenderer& r, const RenderState& state)
  {
    RenderState s(state);

    s.transform = state.transform * this->getTransformation();
    r.draw(this->_geom, &this->_texture, this->_shader, s, GL_QUADS);
  }

  Image::~Image()
  {
  }

}
