#ifndef		__MODELLOADINGEXCEPTION_HH__
# define	__MODELLOADINGEXCEPTION_HH__

# include	<string>
# include	<stdexcept>

namespace	bbm
{
  class		ModelLoadingException : public std::exception
  {
  private :
    const std::string	_message;

  public :
    ModelLoadingException(const std::string&);
    virtual ~ModelLoadingException() throw();

  public :
    const char*	what() const throw();
  };
}

#endif
