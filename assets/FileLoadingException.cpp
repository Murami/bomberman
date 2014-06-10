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
