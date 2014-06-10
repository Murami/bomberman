#ifndef FRAMEMANAGER_HH
#define FRAMEMANAGER_HH

#include "game/Timer.hh"

namespace bbm
{
  class FrameManager
  {
  private:
    Timer		_timer;
    unsigned int	_time;
    unsigned int	_period;
    unsigned int	_frameRate;

  public:
    FrameManager(unsigned int frameRate);
    ~FrameManager();

    // Resets the internal timer. Must be called before the frame loop
    void		start();

    // Updates last frame time and sleep the need time
    void		update();

    // Returns the time of last frame in millisecond
    unsigned int	getTime() const;

    // Returns the frame rate in frame per second
    unsigned int	getFrameRate() const;

    // Sets the frame rate in frame per second
    void		setFrameRate(unsigned int frameRate);
  };
};

#endif /* FRAMEMANAGER_HH */
