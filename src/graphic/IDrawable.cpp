//
// IDrawable.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:30:45 2014 otoshigami
// Last update Sun Jun 15 08:30:46 2014 otoshigami
//

#include "graphic/IDrawable.hh"
#include "OpenGL.hh"

namespace
{
  std::map<std::string, int> create_map()
  {
    std::map<std::string, int> m;
    m["GL_QUADS"] = GL_QUADS;
    return m;
  }
}

std::map<std::string, int> const bbm::IDrawable::primitives = create_map();
