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

    std::map<int, void (Input::*)(const SDL_Event&)>		_updateMethods;

    std::vector<Joystick>	_joysticks;
    std::list<int>		_activeKeys;
    std::list<int>		_pressedKeys;
    std::list<int>		_releasedKeys;
    std::list<int>		_activeMouseButtons;
    std::list<int>		_pressedMouseButtons;
    std::list<int>		_releasedMouseButtons;
    glm::ivec2			_cursorPosition;
    glm::ivec2			_cursorDelta;
    glm::ivec2			_wheelDelta;
    std::list<int>		_events;

  public:
    Input();
    virtual ~Input();

    void			update();
    void			clear();
    int				getAxis(unsigned int axis, unsigned int joystick) const;
    int				getAxisDelta(unsigned int axis, unsigned int joystick) const;
    bool			getButton(unsigned int button, unsigned int joystick) const;
    bool			getButtonDown(unsigned int button, unsigned int joystick) const;
    bool			getButtonUp(unsigned int button, unsigned int joystick) const;
    int				getJoystickNum() const;
    bool			getKey(unsigned int key) const;
    bool			getKeyDown(unsigned int key) const;
    bool			getKeyUp(unsigned int key) const;
    bool			getMouseButton(unsigned int button) const;
    bool			getMouseButtonDown(unsigned int button) const;
    bool			getMouseButtonUp(unsigned int button) const;
    glm::ivec2			getCursorPosition() const;
    glm::ivec2			getCursorDelta() const;
    glm::ivec2			getWheelDelta() const;
    bool			getEvent(unsigned int event) const;

  private:
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
