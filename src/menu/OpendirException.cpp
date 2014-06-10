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
