#ifndef SHADERMANAGER_HH
#define SHADERMANAGER_HH

#include <string>
#include <map>

#include <BasicShader.hh>

namespace bbm
{
  class ShaderManager
  {
    static ShaderManager*			_instance;
    std::map<std::string, gdl::BasicShader*>	_shaders;

  private:
    ShaderManager();
    ~ShaderManager();

  public:
    void			addShader(const std::string& name, const std::string& vertex, const std::string& fragment);
    void			delShader(const std::string& name);
    gdl::BasicShader*		getShader(const std::string& name) const;
    static ShaderManager*	getInstance();
    static void			deleteInstance();
  };
};

#endif /* SHADERMANAGER_HH */
