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
