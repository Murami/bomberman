//
// FrameManager.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:03 2014 otoshigami
// Last update Sun Jun 15 08:36:04 2014 otoshigami
//

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
