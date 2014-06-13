//
// FileExplorer.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun  4 22:38:54 2014 Manu
// Last update Fri Jun 13 01:15:11 2014 Manu
//

#include		<unistd.h>
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
	    if (tmp.find(".save") != std::string::npos)
	      {
	    	std::cout << "pushing " << tmp << std::endl;
	    	this->_filenames.push_back(tmp);
	      }
	  }
      }
  }

  const std::string& FileExplorer::getCurrentFile()
  {
    return (this->_filenames[this->_index]);
  }

  const std::string& FileExplorer::getCurrentTexture()
  {
    static std::string icone;
    icone = "./saves/";
    for (size_t i = 0; i < this->_filenames[this->_index].size(); i++)
      {
	if (this->_filenames[this->_index][i] == '.')
	  break;
	icone += this->_filenames[this->_index][i];
      }
    icone += std::string(".tga");
    if (access(icone.c_str(), F_OK) == -1)
      icone = "./saves/default.tga";
    return (icone);
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
