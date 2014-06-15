//
// TileManager.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:29:10 2014 otoshigami
// Last update Sun Jun 15 08:29:11 2014 otoshigami
//

#include <cstdlib>
#include "game/TileManager.hh"

namespace bbm
{
  TileManager*	TileManager::_instance = NULL;

  TileManager::TileManager()
  {
  }

  TileManager::~TileManager()
  {
  }

  void		TileManager::addTile(const std::string& name, IDrawable* drawable)
  {
    if (_drawables.find(name) == _drawables.end())
      _drawables[name] = drawable;
  }

  void		TileManager::delTile(const std::string& name)
  {
    DrawableListIt	it;

    if ((it = _drawables.find(name)) != _drawables.end())
      _drawables.erase(it);
  }

  IDrawable*	TileManager::getTile(const std::string& name) const
  {
    ConstDrawableListIt	it;

    if ((it = _drawables.find(name)) != _drawables.end())
      return (it->second);
    return (NULL);
  }

  TileManager*	TileManager::getInstance()
  {
    if (!_instance)
      _instance = new TileManager;
    return (_instance);
  }

  void		TileManager::deleteInstance()
  {
    if (_instance)
      {
	delete _instance;
	_instance = NULL;
      }
  }
};
