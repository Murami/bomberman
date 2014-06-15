//
// Screen.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:19 2014 otoshigami
// Last update Sun Jun 15 08:34:20 2014 otoshigami
//

#ifndef SCREEN_HH
#define SCREEN_HH

#include <SdlContext.hh>

#include "ARenderer.hh"

namespace bbm
{
  class	Screen : public ARenderer
  {
  private:
    gdl::SdlContext		_context;
    glm::ivec2			_size;

  public:
    Screen(const std::string& name);
    ~Screen();

    void		draw(gdl::Geometry& geometry, gdl::Texture* texture, gdl::BasicShader* shader,
			     const RenderState& renderState, int primitive, const glm::vec4& color);
    void		draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& renderState,
			     float time, const glm::vec4& color);

    void		flush();
    void		split(const glm::ivec2& position, const glm::ivec2& size) const;
    void		clear(const glm::ivec4& color = glm::ivec4(0, 0, 0, 0)) const;
    glm::vec2		getSize();

    using	ARenderer::draw;
  };
};

#endif /* SCREEN_HH */
