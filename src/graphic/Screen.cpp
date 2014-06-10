#include <iostream>

#include "graphic/Screen.hh"
#include "graphic/IDrawable.hh"
#include "graphic/RenderState.hh"

namespace bbm
{
  Screen::Screen(glm::vec2 size, const std::string& name)
  {
    _size = size;
    _context.start(size.x, size.y, name, SDL_INIT_VIDEO, SDL_WINDOW_OPENGL // | SDL_WINDOW_FULLSCREEN
		   );
  }

  Screen::~Screen()
  {
    // _context.stop();
  }

  void	 Screen::draw(gdl::Geometry& geometry, gdl::Texture* texture,
		      gdl::BasicShader* shader, const RenderState& renderState,
		      int primitive)
  {
    texture->bind();

    shader->bind();
    shader->setUniform("view", renderState.camera.getMatrix());
    shader->setUniform("projection", renderState.projection.getMatrix());
    geometry.draw(*shader, renderState.transform.getMatrix(), primitive);
  }

  void	Screen::draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& renderState, float time)
  {
    shader->bind();
    shader->setUniform("view", renderState.camera.getMatrix());
    shader->setUniform("projection", renderState.projection.getMatrix());
    model.draw(*shader, renderState.transform.getMatrix(), /*time*/ 0);
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
};
