//
// ModelManager.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:33:57 2014 otoshigami
// Last update Sun Jun 15 08:33:58 2014 otoshigami
//

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
