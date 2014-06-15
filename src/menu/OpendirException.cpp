//
// OpendirException.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:48:09 2014 Manu
// Last update Sun Jun 15 11:48:10 2014 Manu
//

#include		"OpendirException.hh"

namespace		bbm
{

  OpendirException::OpendirException(const std::string& message) : FileLoadingException(message)
  {
  }

  const char*		OpendirException::what() const throw()
  {
    return (this->_message.c_str());
  }

  OpendirException::~OpendirException() throw()
  {
  }

}
