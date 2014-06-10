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

  public:
    Joystick();
    virtual ~Joystick();

    // Clears last frame inputs
    void		clear();

    // Returns the axis positions for the given axis
    int			getAxis(unsigned int axis) const;

    // Returns the axis delta since the last update for the given axis
    int			getAxisDelta(unsigned int axis) const;

    // Returns true if the given button is actualy pressed
    bool		getButton(unsigned int button) const;

    // Returns true if the given button was pressed during the last frame
    bool		getButtonDown(unsigned int button) const;

    // Returns true if the given button was relaesed during the last frame
    bool		getButtonUp(unsigned int button) const;

    /*
    ** Update Methods
    */
    void		onAxisMotion(const SDL_Event& event);
    void		onPressedButton(const SDL_Event& event);
    void		onReleasedButton(const SDL_Event& event);
  };
};

#endif /* JOYSTICK_HH */
