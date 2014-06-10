#include <cmath>
#include <sstream>
#include "graphic/Utils.hh"

namespace bbm
{
  float	snap(float value)
  {
    if (value - std::floor(value) > std::ceil(value) - value)
      return (std::ceil(value));
    return (std::floor(value));
  }
};
