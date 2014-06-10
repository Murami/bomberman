#ifndef		__FILELOADINGEXCEPTION_HH__
# define	__FILELOADINGEXCEPTION_HH__

# include	<string>
# include	<stdexcept>

namespace	bbm
{
  class		FileLoadingException : public std::exception
  {
  private :
    const std::string	_message;

  public :
    FileLoadingException(const std::string&);
    virtual ~FileLoadingException() throw();

  public :
    const char*	what() const throw();
  };
}

#endif
