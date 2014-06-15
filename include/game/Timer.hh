//
// Timer.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:38:07 2014 otoshigami
// Last update Sun Jun 15 08:38:07 2014 otoshigami
//

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
