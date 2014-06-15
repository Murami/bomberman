//
// Timer.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:29:35 2014 otoshigami
// Last update Sun Jun 15 08:29:36 2014 otoshigami
//

#include "game/Timer.hh"

namespace bbm
{
  Timer::Timer()
  {
    this->reset();
  }

  Timer::~Timer()
  {
  }

  void		Timer::reset()
  {
    _ticks = SDL_GetTicks();
  }

  unsigned int	Timer::getElapsedTime()
  {
    return (SDL_GetTicks() - _ticks);
  }
};
