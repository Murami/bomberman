#ifndef UTILS_HH
#define UTILS_HH

#include <sstream>
#include <string>

namespace bbm
{
  float		snap(float value);

  template<typename T>
  std::string	toString(const T& value)
  {
    std::stringstream	str;

    str << value << std::endl;
    return (str.str());
  }

};

#endif /* UTILS_HH */
