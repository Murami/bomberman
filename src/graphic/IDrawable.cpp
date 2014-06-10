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
