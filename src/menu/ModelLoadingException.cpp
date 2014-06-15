//
// ModelLoadingException.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:48:13 2014 Manu
// Last update Sun Jun 15 11:48:14 2014 Manu
//

#include		"ModelLoadingException.hh"

namespace		bbm
{

  ModelLoadingException::ModelLoadingException(const std::string& message) :
    _message(message)
  {
  }

  const char*		ModelLoadingException::what() const throw()
  {
    return (this->_message.c_str());
  }

  ModelLoadingException::~ModelLoadingException() throw()
  {
  }

}
