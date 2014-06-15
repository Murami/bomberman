//
// IDrawable.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:33:45 2014 otoshigami
// Last update Sun Jun 15 08:33:46 2014 otoshigami
//

#ifndef IDRAWABLE_HH
#define IDRAWABLE_HH

#include <map>
#include <string>

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	IDrawable
  {
    friend class ARenderer;

  public:
    virtual ~IDrawable() {}
    static const std::map<std::string, int> primitives;

  protected:
    virtual void	draw(ARenderer& renderer, const RenderState& renderState) = 0;
  };
};

#endif /* IDRAWABLE_HH */
