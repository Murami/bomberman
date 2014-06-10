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
    Screen(glm::vec2 size, const std::string& name);
    ~Screen();

    void	draw(gdl::Geometry& geometry, gdl::Texture* texture, gdl::BasicShader* shader, const RenderState& renderState, int primitive);
    void	draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& renderState, float time);

    void	flush();
    void	split(const glm::ivec2& position, const glm::ivec2& size) const;
    void	clear(const glm::ivec4& color = glm::ivec4(0, 0, 0, 0)) const;

    using	ARenderer::draw;
  };
};

#endif /* SCREEN_HH */
