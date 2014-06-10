#ifndef WALL_HH
#define WALL_HH

#include "graphic/Object.hh"

namespace bbm
{
  class	Wall : public Object
  {
  public:
    Wall(const std::string& texture, const std::string& shader);
    ~Wall();
  };
};

#endif /* WALL_HH */
