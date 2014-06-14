#include <iostream>

#include "graphic/Screen.hh"
#include "graphic/IDrawable.hh"
#include "graphic/RenderState.hh"

namespace bbm
{
  Screen::Screen(const std::string& name)
  {
    SDL_DisplayMode	current;


    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_GetCurrentDisplayMode(0, &current) == 0)
      {
	_size.x = current.w;
	_size.y = current.h;

	_context.start(_size.x, _size.y, name, SDL_INIT_VIDEO, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
      }
    else
      {
	std::cout << SDL_GetError() << std::endl;
	_size.x = 1600;
	_size.y = 900;

	_context.start(_size.x, _size.y, name, SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
      }
  }

  Screen::~Screen()
  {
    // _context.stop();
  }

  void	 Screen::draw(gdl::Geometry& geometry, gdl::Texture* texture,
		      gdl::BasicShader* shader, const RenderState& renderState,
		      int primitive, const glm::vec4& color)
  {
    if (texture && shader)
      {
	texture->bind();

	shader->bind();
	shader->setUniform("view", renderState.camera.getMatrix());
	shader->setUniform("projection", renderState.projection.getMatrix());
	shader->setUniform("color", color);
	geometry.draw(*shader, renderState.transform.getMatrix(), primitive);
      }
  }

  void	Screen::draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& renderState, float time,
		     const glm::vec4& color)
  {
    if (shader)
      {
	shader->bind();
	shader->setUniform("view", renderState.camera.getMatrix());
	shader->setUniform("projection", renderState.projection.getMatrix());
	shader->setUniform("color", color);
	model.draw(*shader, renderState.transform.getMatrix(), time);
      }
  }

  void	Screen::split(const glm::ivec2& position, const glm::ivec2& size) const
  {
    glViewport(position.x, position.y, size.x, size.y);
    glScissor(position.x, position.y, size.x, size.y);
  }

  void	Screen::clear(const glm::ivec4& color) const
  {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void	 Screen::flush()
  {
    _context.flush();
  }

  glm::vec2	Screen::getSize()
  {
    return (glm::vec2(_size.x, _size.y));
  }
};
