#ifndef JOYSTICK_HH
#define JOYSTICK_HH

#include <vector>
#include <list>
#include <glm/gtc/type_precision.hpp>
#include <SDL.h>

namespace bbm
{
  // Handle the inputs for one joystick
  class	Joystick
  {
  public:
    struct	Axis
    {
      int		_lastPosition;
      int		_position;
    };

  private:
    typedef std::vector<Axis>::iterator	AxesListIt;
    typedef std::list<int>::iterator	EventIt;

  private:
    std::list<int>	_activeButtons;
    std::list<int>	_pressedButtons;
    std::list<int>	_releasedButtons;
    std::vector<Axis>	_axes;
    SDL_Joystick*	_joystickSDL;

  public:
    Joystick(int i);
    Joystick(const Joystick& joystick);
    virtual ~Joystick();

    void		clear();
    int			getAxis(unsigned int axis) const;
    int			getAxisDelta(unsigned int axis) const;
    bool		getButton(unsigned int button) const;
    bool		getButtonDown(unsigned int button) const;
    bool		getButtonUp(unsigned int button) const;
    void		onAxisMotion(const SDL_Event& event);
    void		onPressedButton(const SDL_Event& event);
    void		onReleasedButton(const SDL_Event& event);
  };
};

#endif /* JOYSTICK_HH */
