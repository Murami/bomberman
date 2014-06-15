//
// Model.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:30:49 2014 otoshigami
// Last update Sun Jun 15 08:30:50 2014 otoshigami
//

#include <iostream>
#include <exception>
#include <stdexcept>
#include "graphic/Model.hh"
#include "graphic/Transform.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "graphic/ModelManager.hh"

namespace bbm
{
  Model::Model(const std::string& name,
	       const std::string& shader,
	       float speed)
  {
    _model = ModelManager::getInstance()->getModel(name);
    _elapsedTime = 0;
    _shader = ShaderManager::getInstance()->getShader(shader);
    _speed = speed;
  }

  Model::~Model()
  {
  }

  void	 Model::setShader(const std::string& shader)
  {
    _shader = ShaderManager::getInstance()->getShader(shader);
  }

  void	 Model::setCurrentAnimation(const std::string& animation, bool loop)
  {
    _model->setCurrentSubAnim(animation, loop);
  }

  void	 Model::pause()
  {
    _model->pause(true);
  }

  void	 Model::play()
  {
    _model->pause(false);
  }

  void	Model::update(float time)
  {
    _elapsedTime = time * _speed;
  }

  void	Model::draw(ARenderer& renderer, const RenderState& renderState)
  {
    if (_model != NULL)
      {
	RenderState	newState = renderState;
	newState.transform *= getTransform();
	renderer.draw(*_model, _shader, newState, _elapsedTime, glm::vec4(1, 1, 1, 1));
      }
  }
};
