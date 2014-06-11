#include <exception>
#include <stdexcept>
#include "graphic/ModelManager.hh"

namespace bbm
{
  ModelManager::ModelManager()
  {
  }

  ModelManager::~ModelManager()
  {
  }

  void		ModelManager::addModel(const std::string& name, const std::string& pathname)
  {
    gdl::Model*	model;

    if (_models.find(name) != _models.end())
      return;
    model = new gdl::Model;
    if (!model->load(pathname))
      throw (std::runtime_error("error loading model"));
    _models[name] = model;
  }

  void		ModelManager::delModel(const std::string& name)
  {
    if (_models.find(name) == _models.end())
      return;
    delete _models[name];
    _models.erase(_models.find(name));
  }

  gdl::Model*	ModelManager::getModel(const std::string& name)
  {
    if (_models.find(name) != _models.end())
      return (_models.at(name));
    return (NULL);
  }


  ModelManager*	ModelManager::getInstance()
  {
    if (_instance == NULL)
      _instance = new ModelManager;
    return (_instance);
  }

  void		ModelManager::deleteInstance()
  {
    if (_instance == NULL)
      return;
    delete _instance;
    _instance = NULL;
  }
};
