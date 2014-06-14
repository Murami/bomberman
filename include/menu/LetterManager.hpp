//
// LetterManager.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun  4 09:46:06 2014 Manu
// Last update Sat Jun 14 18:17:24 2014 Manu
//

#ifndef		__LETTERMANAGER_HPP__
# define	__LETTERMANAGER_HPP__

# include	<string>
# include	<map>
# include	"Texture.hh"
# include	"Letter.hh"
# include	"FileLoadingException.hh"

namespace	bbm
{

  class		Letter;

  class		LetterManager
  {
  private :
    std::map<char, gdl::Texture*>	_alphabet;
    std::map<char, gdl::Texture*>	_numbers;
    gdl::Texture*	    		_space;
    gdl::Texture*			_slash;
    gdl::Texture*			_underscore;
    gdl::Texture*			_twoDots;

  public :
    static LetterManager*		_instance;

  public : static LetterManager*	getInstance()
    {
      if (_instance == NULL)
	_instance = new LetterManager();
      return (_instance);
    }

  public : gdl::Texture*	getLetter(char c)
    {
      if (c == ' ')
	return (this->_space);
      else if (c == '_')
	return (this->_underscore);
      else if (c == '/')
	return (this->_slash);
      else if (c == ':')
	return (this->_twoDots);
      else if (c >= '0' && c <= '9')
	return (this->_numbers[c]);
      else if (c >= 'a' && c <= 'z')
	return (this->_alphabet[c]);
      return (NULL);
    }

  public : LetterManager()
    {
      this->_slash = new gdl::Texture();
      if (!this->_slash->load(Letter::TEXTURE_PATH +
			      std::string("letter_slash.tga")))
	throw (FileLoadingException("letter_slash.tga"));
      this->_underscore = new gdl::Texture();
      if (!this->_underscore->load(Letter::TEXTURE_PATH +
				   std::string("letter_underscore.tga")))
	throw (FileLoadingException("letter_underscore.tga"));
      this->_space = new gdl::Texture();
      if (!this->_space->load(Letter::TEXTURE_PATH +
			      std::string("letter_space.tga")))
	throw (FileLoadingException("letter_space.tga"));
      this->_twoDots = new gdl::Texture();
      if (!this->_twoDots->load(Letter::TEXTURE_PATH +
				std::string("letter_twodots.tga")))
	throw (FileLoadingException("Letter_twodots.tga"));
      for (char cpt = 'a'; cpt <= 'z'; cpt++)
	{
	  this->_alphabet[cpt] = new gdl::Texture();
	  std::string path(Letter::TEXTURE_PATH +
			   std::string("letter_") +
			   cpt + std::string(".tga"));
	  if (!this->_alphabet[cpt]->load(path))
	    throw (FileLoadingException(path));
	}
      for (char cpt = '0'; cpt <= '9'; cpt++)
	{
	  this->_numbers[cpt] = new gdl::Texture();
	  std::string path(Letter::TEXTURE_PATH +
			   std::string("letter_") +
			   cpt + std::string(".tga"));
	  if (!this->_numbers[cpt]->load(path))
	    throw (FileLoadingException(path));
	}
    }

  public : ~LetterManager()
    {
    }

  };

}

#endif
