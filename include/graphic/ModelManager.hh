#ifndef MODELMANAGER_HH
#define MODELMANAGER_HH

#include <map>
#include <string>

#include <Model.hh>

namespace bbm
{
  class	ModelManager
  {
  private:
    ModelManager();
    ~ModelManager();

  public:
    void			addModel(const std::string& name, const std::string& pathname);
    void			delModel(const std::string& name);
    gdl::Model*			getModel(const std::string& name);

    static ModelManager*	getInstance();
    static void			deleteInstance();

  public:
    static ModelManager*		_instance;
    std::map<std::string, gdl::Model*>	_models;
  };
};

#endif /* MODELMANAGER_HH */
