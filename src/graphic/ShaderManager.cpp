//
// ShaderManager.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:25 2014 otoshigami
// Last update Sun Jun 15 08:31:27 2014 otoshigami
//

#include <cstdlib>
#include "graphic/ShaderManager.hh"

namespace bbm
{
  ShaderManager*	ShaderManager::_instance = NULL;

  ShaderManager::ShaderManager()
  {
  }

  ShaderManager::~ShaderManager()
  {
  }

  void			ShaderManager::addShader(const std::string& name, const std::string& vertex, const std::string& fragment)
  {
    gdl::BasicShader*	shader = new gdl::BasicShader;

    if (getShader(name) != NULL)
      return;

    shader->load(vertex, GL_VERTEX_SHADER);
    shader->load(fragment, GL_FRAGMENT_SHADER);
    shader->build();
    _shaders[name] = shader;
  }

  void			ShaderManager::delShader(const std::string& name)
  {
    gdl::AShader*	shader;

    if ((shader = getShader(name)) == NULL)
      return;
    _shaders.erase(_shaders.find(name));
    delete shader;
  }

  gdl::BasicShader*		ShaderManager::getShader(const std::string& name) const
  {
    if (_shaders.find(name) != _shaders.end())
      return (_shaders.at(name));
    return (NULL);
  }

  ShaderManager*	ShaderManager::getInstance()
  {
    if (_instance == NULL)
      _instance = new ShaderManager;
    return (_instance);
  }

  void			ShaderManager::deleteInstance()
  {
    if (_instance == NULL)
      return;
    delete _instance;
    _instance = NULL;
  }
};
