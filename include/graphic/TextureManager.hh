#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <string>
#include <map>
#include <Texture.hh>

namespace bbm
{
  // A simple manager for textures
  class	TextureManager
  {
  private:
    static TextureManager*			_instance;
    std::map<std::string, gdl::Texture*>	_textures;

  private:
    TextureManager();
    ~TextureManager();

  public:

    // Loads a texture from a filename. If the texture is loaded then this function do nothing
    void			addTexture(const std::string& name, const std::string& filename);

    // Loads a textre form a filename. The associated texuture to the name is replaced by the new texture given as parameter
    void			setTexture(const std::string& name, const std::string& filename);

    // Frees the texture associated with the given name
    void			delTexture(const std::string& name);

    // Returns the texture associated with the given name
    gdl::Texture*		getTexture(const std::string& name) const;

    // Returns the singleton instance
    static TextureManager*	getInstance();

    // Deletes the current instance
    static void			deleteInstance();
  };
};

#endif /* TEXTUREMANAGER_HH */
