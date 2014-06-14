//
// FileExplorer.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun  4 22:38:50 2014 Manu
// Last update Fri Jun 13 23:12:41 2014 Manu
//

#ifndef		__FILEEXPLORER_HH__
# define	__FILEEXPLORER_HH__

# include	<iostream>
# include	<string>
# include	<vector>
# include	<sys/types.h>
# include	<dirent.h>
# include	"OpendirException.hh"

namespace	gdl
{
  class		Texture;
}

namespace	bbm
{

  class		FileExplorer
  {
  private :
    const std::string&		_pathname;
    std::vector<std::string>	_filenames;
    std::vector<std::string>	_iconeNames;
    size_t			_index;
    DIR*			_dirp;
    struct dirent*		_entry;

  public :
    const static std::string	SAVE_PATH;

  public :
    const std::string&		getCurrentFile();
    const std::string&		getCurrentTexture();

  public :
    void			exploreSaves();

  public :
    void			next();
    void			prev();

  public :
    FileExplorer(const std::string&);
    ~FileExplorer();
  };
}

#endif
