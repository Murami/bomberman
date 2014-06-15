//
// ARenderer.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:30:36 2014 otoshigami
// Last update Sun Jun 15 08:30:38 2014 otoshigami
//

#include "graphic/ARenderer.hh"
#include "graphic/IDrawable.hh"

namespace bbm
{
  ARenderer::~ARenderer()
  {
  }

  void	ARenderer::draw(IDrawable& drawable, const RenderState& state)
  {
    drawable.draw(*this, state);
  }
};
