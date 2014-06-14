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

    void		start();
    void		update();
    unsigned int	getTime() const;
    unsigned int	getFrameRate() const;
    void		setFrameRate(unsigned int frameRate);
  };
};

#endif /* FRAMEMANAGER_HH */
