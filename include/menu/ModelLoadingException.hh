//
// ModelLoadingException.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:49:37 2014 Manu
// Last update Sun Jun 15 11:49:38 2014 Manu
//

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
