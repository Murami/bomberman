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
	renderer.draw(*_model, _shader, newState, _elapsedTime);
      }
  }
};
