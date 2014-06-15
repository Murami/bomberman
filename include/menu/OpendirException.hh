//
// OpendirException.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:49:31 2014 Manu
// Last update Sun Jun 15 11:49:31 2014 Manu
//

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
