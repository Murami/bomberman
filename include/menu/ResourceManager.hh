//
// ResourceManager.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_4
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 16 12:20:46 2014 Manu
// Last update Fri May 30 10:49:49 2014 Manu
//

#ifndef		__RESOURCEMANAGER_HH__
# define	__RESOURCEMANAGER_HH__

# include	<vector>
# include	<iostream>

class		ResourceManager
{
private :
  static ResourceManager*	_instance;

public :
  static ResourceManager*	getInstance();

public :
  ResourceManager();
  ~ResourceManager();

};

#endif
