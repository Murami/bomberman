//
// Marvin.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:30:41 2014 quentin desabre
// Last update Sun Jun 15 09:03:26 2014 Desabre Quentin
//

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
    _color = glm::vec4(1, 1, 1, 1);
  }

  Marvin::~Marvin()
  {
  }

  void	Marvin::setColor(const glm::vec4& color)
  {
    _color = color;
  }

  void	Marvin::initialize()
  {
    _animations.resize(54 - 38);

    for (int i = 38; i < 54; i++)
      {
	_animations[i - 38] = new gdl::Model;
	_animations[i - 38]->load("./gdl/assets/marvin.fbx");
	_animations[i - 38]->createSubAnim(0, "run", i, i + 1);
	_animations[i - 38]->setCurrentSubAnim("run", true);
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
    renderer.draw(*_animations[elapsedTimeInt % (54 - 38)], _shader, newState, 0, _color);
  }
};
