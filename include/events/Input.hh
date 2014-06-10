#ifndef INPUT_WITH_JOYSTICK_HH
#define INPUT_WITH_JOYSTICK_HH

#include <list>
#include <vector>
#include <map>
#include <glm/gtc/type_precision.hpp>

#include "events/Joystick.hh"

namespace bbm
{
  // Handle the inputs for joystick
  class	Input
  {
  private:
    typedef std::map<int, void (Input::*)(const SDL_Event&)>::iterator	UpdateMethodsIt;
    typedef std::list<int>::iterator					EventListIt;
    typedef std::vector<Joystick>::iterator				JoystickListIt;

    /*
    ** Update methods array
    */
    std::map<int, void (Input::*)(const SDL_Event&)>		_updateMethods;

    /*
    ** Joysticks attributes
    */
    std::vector<Joystick>	_joysticks;

    /*
    ** Keyboards attributes
    */
    std::list<int>		_activeKeys;
    std::list<int>		_pressedKeys;
    std::list<int>		_releasedKeys;

    /*
    ** Mouse attributes
    */
    std::list<int>		_activeMouseButtons;
    std::list<int>		_pressedMouseButtons;
    std::list<int>		_releasedMouseButtons;
    glm::ivec2			_cursorPosition;
    glm::ivec2			_cursorDelta;
    glm::ivec2			_wheelDelta;

    /*
    ** General Events
    */
    std::list<int>		_events;

  public:
    Input();
    virtual ~Input();

    /*
    ** General Methods
    */

    // Retrieves events that occured during last frame and update internal states
    void			update();

    // Clears last frame events
    void			clear();

    /*
    ** Joysticks methods
    */

    // Returns the axis positions for the given joystick and axis
    int				getAxis(unsigned int axis, unsigned int joystick) const;

    // Returns the axis delta since last frame for the given joystick and axis
    int				getAxisDelta(unsigned int axis, unsigned int joystick) const;

    // Returns true if the button passed as parameter is actualy pressed for the given joystick
    bool			getButton(unsigned int button, unsigned int joystick) const;

    // Return true if the button passed as parameter as been pressed during the last frame for the given joystick
    bool			getButtonDown(unsigned int button, unsigned int joystick) const;

    // Return true if the button passed as paramter as been released during the last frame for the given joystick
    bool			getButtonUp(unsigned int button, unsigned int joystick) const;

    // Returns the numbers of connected joysticks
    int				getJoystickNum() const;

    /*
    ** Keyboard methods
    */

    // Returns true if the key passed as parameter is actualy pressed
    bool			getKey(unsigned int key) const;

    // Returns true if the key passed as parameter was pressed during last frame
    bool			getKeyDown(unsigned int key) const;

    // Returns true if the key passed as parameter was released during last frame
    bool			getKeyUp(unsigned int key) const;

    /*
    ** Mouse methods
    */

    // Returns true if the mouse button passed as parameter is actualy pressed
    bool			getMouseButton(unsigned int button) const;

    // Returns true if the mouse button passed as parameter was pressed during last frame
    bool			getMouseButtonDown(unsigned int button) const;

    // Returns true if the mouse button passed as parameter was released during last frame
    bool			getMouseButtonUp(unsigned int button) const;

    // Returns the cursor postion
    glm::ivec2			getCursorPosition() const;

    // Returns the delta of the cursor position since the last frame
    glm::ivec2			getCursorDelta() const;

    // Returns the wheel delta since the last frame
    glm::ivec2			getWheelDelta() const;

    /*
    ** Others Events Methods
    */

    // Returns true if the event passed as parameter occured during last frame
    bool			getEvent(unsigned int event) const;

  private:

    /*
    ** Internal Update Methods
    */
    void			onPressedKey(const SDL_Event& event);
    void			onReleasedKey(const SDL_Event& event);
    void			onPressedMouseButton(const SDL_Event& event);
    void			onReleasedMouseButton(const SDL_Event& event);
    void			onMouseMotion(const SDL_Event& event);
    void			onWheelMotion(const SDL_Event& event);
    void			onAxisMotion(const SDL_Event& event);
    void			onPressedButton(const SDL_Event& event);
    void			onReleasedButton(const SDL_Event& event);
    void			onUnknownEvent(const SDL_Event& event);
  };
};

#endif /* INPUT_WITH_JOYSTICK_HH */
