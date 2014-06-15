//
// Utils.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:41 2014 otoshigami
// Last update Sun Jun 15 08:34:42 2014 otoshigami
//

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
