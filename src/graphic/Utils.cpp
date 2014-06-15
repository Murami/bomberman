//
// Utils.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:45 2014 otoshigami
// Last update Sun Jun 15 08:31:46 2014 otoshigami
//

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
