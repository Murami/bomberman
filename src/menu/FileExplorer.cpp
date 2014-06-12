//
// FileExplorer.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun  4 22:38:54 2014 Manu
// Last update Thu Jun 12 19:23:10 2014 Manu
//

#include		"FileExplorer.hh"

namespace		bbm
{

  const std::string FileExplorer::SAVE_PATH("./saves");

  FileExplorer::FileExplorer(const std::string& pathname) : _pathname(pathname)
  {
    this->_index = 0;
    this->_dirp = NULL;
    this->_entry = NULL;
  }

  void			FileExplorer::exploreSaves()
  {
    if ((this->_dirp = opendir(SAVE_PATH.c_str())) == NULL)
      {
	throw (OpendirException(SAVE_PATH));
      }
    while ((this->_entry = readdir(this->_dirp)))
      {
	if (this->_entry->d_name[0] != '.')
	  {
	    std::string tmp(this->_entry->d_name);
	    if (tmp.find(".tga") != std::string::npos)
	      this->_iconeNames.push_back(tmp);
	    else if (tmp.find(".save") != std::string::npos)
	      this->_filenames.push_back(tmp);
	  }
      }
  }

  const std::string&	FileExplorer::getCurrentFile()
  {
    return (this->_filenames[this->_index]);
  }

  const std::string&	FileExplorer::getCurrentTexture()
  {
    return (this->_iconeNames[this->_index]);
  }

  void			FileExplorer::next()
  {
    this->_index++;
    if (this->_index == this->_filenames.size())
      this->_index = 0;
  }

  void			FileExplorer::prev()
  {
    if (this->_index == 0)
      this->_index = this->_filenames.size() - 1;
    else
      this->_index--;
  }

  FileExplorer::~FileExplorer()
  {
  }

}
