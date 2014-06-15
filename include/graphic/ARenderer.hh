//
// ARenderer.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:33:37 2014 otoshigami
// Last update Sun Jun 15 08:33:38 2014 otoshigami
//

#ifndef ARENDERER_HH
#define ARENDERER_HH

#include <Texture.hh>
#include <BasicShader.hh>
#include <Geometry.hh>
#include <Model.hh>

namespace bbm
{
  class IDrawable;
  class	RenderState;

  class	ARenderer
  {
  public:
    virtual ~ARenderer();

    void		draw(IDrawable& drawable, const RenderState& state);
    virtual void	draw(gdl::Geometry& geometry, gdl::Texture* texture, gdl::BasicShader* shader,
			     const RenderState& state, int primitive, const glm::vec4& color) = 0;
    virtual void	draw(gdl::Model& model, gdl::BasicShader* shader, const RenderState& state,
			     float time, const glm::vec4& color) = 0;
  };
};

#endif /* ARENDERER_HH */
