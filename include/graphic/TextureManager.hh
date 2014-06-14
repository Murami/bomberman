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
