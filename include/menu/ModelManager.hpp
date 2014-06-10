//
// ModelManager.hpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun  4 10:50:26 2014 Manu
// Last update Wed Jun  4 17:03:05 2014 Manu
//

#ifndef		__MODEL_MANAGER_HPP__
# define	__MODEL_MANAGER_HPP__

# include	<string>
# include	<map>
# include	"Model.hh"

namespace	bbm
{
  class		ModelManager
  {
  private :
    std::map<std::string, gdl::Model*>	_models;
    static ModelManager*	_instance;

  public :
    static ModelManager*	getInstance()
    {
      if (_instance == NULL)
	_instance = new ModelManager();
      return (_instance);
    }

  public :
    gdl::Model* getModel(const std::string& name)
    {
      return (_models[name]);
    }

  public :
    ModelManager()
    {
      this->_models["selector"] = new gdl::Model();
      this->_models["selector"]->load("./assets/menu/models/arrow.obj");
    }

    ~ModelManager()
    {
    }
  };
}

#endif
