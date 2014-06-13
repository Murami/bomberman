#include "graphic/Utils.hh"
#include "entity/Marvin.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"

#include <iostream>
#include <unistd.h>

namespace bbm
{
  std::vector<gdl::Model*>	Marvin::_animations;

  Marvin::Marvin()
  {
    _elapsedTime = 0;
    _pause = true;
    _shader = ShaderManager::getInstance()->getShader("default");
  }

  Marvin::~Marvin()
  {
  }

  void	Marvin::initialize()
  {
    _animations.resize(54 - 38);

    for (int i = 38; i < 54; i++)
      {
	_animations[i - 38] = new gdl::Model;
	if (_animations[i - 38]->load("./gdl/assets/marvin.fbx") == true)
	  std::cout << "load = true" << std::endl;
	if (_animations[i - 38]->createSubAnim(0, "run", i, i + 1) == true)
	  std::cout << "create sub = true" << std::endl;
	if (_animations[i - 38]->setCurrentSubAnim("run", true) == true)
	  std::cout << "set current = true" << std::endl;
	std::cout << "sleep de 1" << std::endl;
	sleep(1);
      }
  }

  void	Marvin::release()
  {
    for (int i = 38; i < 54; i++)
      delete _animations[i - 38];
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
