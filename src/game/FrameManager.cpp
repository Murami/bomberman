//
// FrameManager.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:28:03 2014 otoshigami
// Last update Sun Jun 15 08:28:04 2014 otoshigami
//

#include "game/FrameManager.hh"

namespace bbm
{
  FrameManager::FrameManager(unsigned int frameRate)
  {
    _frameRate = frameRate;
    _period = 1000 / frameRate;
    this->start();
  }

  FrameManager::~FrameManager()
  {
  }

  void		FrameManager::start()
  {
    _timer.reset();
    _time = 0;
  }

  void		FrameManager::update()
  {
    _time = _timer.getElapsedTime();
    if (_time < _period)
      SDL_Delay(_period - _time);
    _time = _timer.getElapsedTime();
    _timer.reset();
  }

  unsigned int	FrameManager::getTime() const
  {
    return (_time);
  }

  unsigned int	FrameManager::getFrameRate() const
  {
    return (_frameRate);
  }

  void		FrameManager::setFrameRate(unsigned int frameRate)
  {
    _frameRate = frameRate;
  }
};
