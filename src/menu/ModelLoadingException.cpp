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
