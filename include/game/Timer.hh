#ifndef TIMER_HH
#define TIMER_HH

#include <SDL.h>

namespace bbm
{
  class Timer
  {
  private:
    unsigned int	_ticks;

  public:
    Timer();
    ~Timer();

    // Resets the timer
    void		reset();

    // Returns the time elapsed since the last reset in millisecond
    unsigned int	getElapsedTime();
  };
};

#endif /* TIMER_HH */
