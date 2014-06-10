#include "graphic/Utils.hh"
#include "entity/Marvin.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"

#include <iostream>

namespace bbm
{
  bool				Marvin::_initialized = false;
  std::vector<gdl::Model*>	Marvin::_animations;

  Marvin::Marvin()
  {
    _animations.resize(54 - 38);

    if (!_initialized)
      {
	_initialized = true;
	for (int i = 38; i < 54; i++)
	  {
	    _animations[i - 38] = new gdl::Model;
	    _animations[i - 38]->load("./gdl/assets/marvin.fbx");
	    _animations[i - 38]->createSubAnim(0, "run", i, i + 1);
	    _animations[i - 38]->setCurrentSubAnim("run", true);
	  }
      }
    _pause = true;
    _shader = ShaderManager::getInstance()->getShader("default");
  }

  Marvin::~Marvin()
  {
  }

  void	Marvin::update(float time)
  {
    if (!_pause)
      _elapsedTime += time * 0.025;
  }

  void	Marvin::pause()
  {
    _pause = true;
  }

  void	Marvin::play()
  {
    _pause = false;
  }

  void	Marvin::draw(ARenderer& renderer, const RenderState& renderState)
  {
    RenderState	newState = renderState;
    int		elapsedTimeInt = _elapsedTime;

    newState.transform *= getTransform();
    renderer.draw(*_animations[elapsedTimeInt % (54 - 38)], _shader, newState, 0);
  }
};
