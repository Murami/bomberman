//
// FileLoadingException.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:50:03 2014 Manu
// Last update Sun Jun 15 11:50:04 2014 Manu
//

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
    const char*		what() const throw();
  };
}

#endif
