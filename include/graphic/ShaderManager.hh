#ifndef SHADERMANAGER_HH
#define SHADERMANAGER_HH

#include <string>
#include <map>
#include <BasicShader.hh>

namespace bbm
{
  // A simple manager for shaders
  class ShaderManager
  {
    static ShaderManager*			_instance;
    std::map<std::string, gdl::BasicShader*>	_shaders;

  private:

    // Private constructor for singleton
    ShaderManager();

    // Private destructor for singleton
    ~ShaderManager();

  public:

    // Loads a shader and add it to the manager if it's already loaded
    void			addShader(const std::string& name, const std::string& vertex, const std::string& fragment);

    // Frees the shader for the given name
    void			delShader(const std::string& name);

    // Returns the shaders for the given name
    gdl::BasicShader*		getShader(const std::string& name) const;

    // Returns the singleton instance and create it if necesary
    static ShaderManager*	getInstance();

    // Deletes the current instances or do nothing if the manager is not instancied
    static void			deleteInstance();
  };
};

#endif /* SHADERMANAGER_HH */
