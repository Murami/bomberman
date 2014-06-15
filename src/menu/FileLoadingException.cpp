//
// FileLoadingException.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:48:45 2014 Manu
// Last update Sun Jun 15 11:48:45 2014 Manu
//

#include		"FileLoadingException.hh"

namespace		bbm
{

  FileLoadingException::FileLoadingException(const std::string& message) :
    _message(message)
  {
  }

  const char*		FileLoadingException::what() const throw()
  {
    return (this->_message.c_str());
  }

  FileLoadingException::~FileLoadingException() throw()
  {
  }

}
