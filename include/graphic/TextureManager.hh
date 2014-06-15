//
// TextureManager.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:28 2014 otoshigami
// Last update Sun Jun 15 08:34:29 2014 otoshigami
//

#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <string>
#include <map>

#include <Texture.hh>

namespace bbm
{
  class	TextureManager
  {
  private:
    static TextureManager*			_instance;
    std::map<std::string, gdl::Texture*>	_textures;

  private:
    TextureManager();
    ~TextureManager();

  public:
    void			addTexture(const std::string& name, const std::string& filename);
    void			setTexture(const std::string& name, const std::string& filename);
    void			delTexture(const std::string& name);
    gdl::Texture*		getTexture(const std::string& name) const;
    static TextureManager*	getInstance();
    static void			deleteInstance();
  };
};

#endif /* TEXTUREMANAGER_HH */
