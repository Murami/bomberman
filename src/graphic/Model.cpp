#include <exception>
#include <stdexcept>
#include "graphic/Model.hh"
#include "graphic/Transform.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"

namespace bbm
{
  Model::Model(const std::string& path,
	       const std::string& shader,
	       float speed)
  {
    if (!_model.load(path))
      throw (std::runtime_error("error while loading model"));
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
    _model.setCurrentSubAnim(animation, loop);
  }

  void	 Model::pause()
  {
    _model.pause(true);
  }

  void	 Model::play()
  {
    _model.pause(false);
  }

  void	Model::update(float time)
  {
    _elapsedTime = time * _speed;
  }

  void	Model::draw(ARenderer& renderer, const RenderState& renderState)
  {
    RenderState	newState = renderState;

    newState.transform *= getTransform();
    renderer.draw(_model, _shader, newState, _elapsedTime);
  }
};
