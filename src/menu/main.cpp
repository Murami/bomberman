#include	<iostream>
#include	"glm/gtc/matrix_transform.hpp"
#include	"glm/glm.hpp"
#include	"Clock.hh"
#include	"Input.hh"
#include	"Model.hh"
#include	"SdlContext.hh"
#include	"Menu.hh"
#include	"BasicShader.hh"
#include	"MenuManager.hh"
#include	"ResourceManager.hh"
#include	"Button.hh"

ResourceManager* ResourceManager::_instance = NULL;

class		Bart : public AObject
{
private :
  gdl::Model	_model;

public :
  virtual bool	initialize()
  {
    if (!_model.load("./models/bart.fbx"))
      return (false);
    this->scale(glm::vec3(5, 5, 5));
    this->_model.setCurrentAnim(0);
    return (true);
  }
  virtual void	update(const gdl::Clock&, gdl::Input&)
  {
  }
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    this->_model.draw(shader, this->getTransformation(), clock.getElapsed());
  }

public :
  Bart() : AObject()
  {
  }
  ~Bart()
  {
  }
};

int		main()
{
  gdl::SdlContext	_context;
  gdl::BasicShader	_shader;
  gdl::Input		_input;
  gdl::Clock		_clock;
  glm::mat4		_projection;
  glm::mat4		_transformation;
  bool			_continue;

  Bart b;

  // MenuManager		_menuManager;

  _context.start(1920, 1080, "Bomberman");
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !_shader.build())
    {
      std::cerr << "shader error" << std::endl;
      return (-1);
    }
  _projection = glm::perspective(60.0f, 1920.0f / 960.0f, 0.1f, 1000.0f);
  _transformation = glm::lookAt(glm::vec3(10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  _continue = true;

  b.initialize();

  // _menuManager.initialize();

  while (_continue)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _context.updateInputs(_input);
      if (_input.getKey(SDLK_ESCAPE))
	_continue = false;
      _context.updateClock(_clock);
      _shader.bind();

      b.update(_clock, _input);
      b.draw(_shader, _clock);

      // _menuManager.update(_clock, _input);
      // _menuManager.draw(_shader, _clock);

      _context.flush();
    }
  return (0);
}
