//
// ResourceManager.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_4
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 16 12:20:49 2014 Manu
// Last update Fri May 30 10:48:53 2014 Manu
//

#include		"ResourceManager.hh"

ResourceManager::ResourceManager()
{
}

ResourceManager*	ResourceManager::getInstance()
{
  if (_instance == NULL)
    _instance = new ResourceManager();
  return (_instance);
}

ResourceManager::~ResourceManager()
{
}
