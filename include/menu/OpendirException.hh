#ifndef		__OPENDIREXCEPTION_HH__
# define	__OPENDIREXCEPTION_HH__

# include	<string>
# include	"FileLoadingException.hh"

namespace	bbm
{
  class		OpendirException : public FileLoadingException
  {
  private :
    const std::string	_message;

  public :
    OpendirException(const std::string&);
    virtual ~OpendirException() throw();

  public :
    const char*	what() const throw();
  };
}

#endif
