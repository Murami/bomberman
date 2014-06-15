//
// TextureManager.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:30 2014 otoshigami
// Last update Sun Jun 15 08:31:31 2014 otoshigami
//

#include "graphic/TextureManager.hh"

namespace bbm
{
  TextureManager*	TextureManager::_instance = NULL;

  TextureManager::TextureManager()
  {
  }

  TextureManager::~TextureManager()
  {
  }

  void			TextureManager::addTexture(const std::string& name, const std::string& filename)
  {
    gdl::Texture*	texture;

    if (getTexture(name) != NULL)
      return;

    texture = new gdl::Texture;
    texture->load(filename);
    _textures[name] = texture;
  }

  void			TextureManager::delTexture(const std::string& name)
  {
    gdl::Texture*	texture;

    if ((texture = getTexture(name)) == NULL)
      return;
    _textures.erase(_textures.find(name));
    delete texture;
  }

  gdl::Texture*		TextureManager::getTexture(const std::string&  name) const
  {
    if (_textures.find(name) != _textures.end())
      return (_textures.at(name));
    return (NULL);
  }

  TextureManager*	TextureManager::getInstance()
  {
    if (_instance == NULL)
      _instance = new TextureManager;
    return (_instance);
  }

  void			TextureManager::deleteInstance()
  {
    if (_instance == NULL)
      return;
    delete _instance;
    _instance = NULL;
  }
};
