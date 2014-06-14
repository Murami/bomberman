#include <iostream>

#include <algorithm>
#include "events/Input.hh"

namespace bbm
{
  Input::Input()
  {
    _updateMethods[SDL_KEYDOWN] = &Input::onPressedKey;
    _updateMethods[SDL_KEYUP] = &Input::onReleasedKey;
    _updateMethods[SDL_MOUSEBUTTONDOWN] = &Input::onPressedMouseButton;
    _updateMethods[SDL_MOUSEBUTTONUP] = &Input::onReleasedMouseButton;
    _updateMethods[SDL_MOUSEMOTION] = &Input::onMouseMotion;
    _updateMethods[SDL_MOUSEWHEEL] = &Input::onWheelMotion;
    _updateMethods[SDL_JOYAXISMOTION] = &Input::onAxisMotion;
    _updateMethods[SDL_JOYBUTTONDOWN] = &Input::onPressedButton;
    _updateMethods[SDL_JOYBUTTONUP] = &Input::onReleasedButton;
    for (int i = 0; i < SDL_NumJoysticks(); i++)
      _joysticks.push_back(Joystick(i));
  }

  Input::~Input()
  {
  }

  void		Input::update()
  {
    SDL_Event		event;
    UpdateMethodsIt	it;

    this->clear();
    while (SDL_PollEvent(&event))
      {
	if ((it = _updateMethods.find(event.type)) != _updateMethods.end())
	  {
	    ((*this).*(it->second))(event);
	    return;
	  }
      }
    this->onUnknownEvent(event);
  }

  void		Input::clear()
  {
    JoystickListIt	it;

    _wheelDelta = glm::ivec2(0, 0);
    _cursorDelta = glm::ivec2(0, 0);
    _pressedKeys.clear();
    _releasedKeys.clear();
    _pressedMouseButtons.clear();
    _releasedMouseButtons.clear();
    _events.clear();
    for (it != _joysticks.begin(); it != _joysticks.end(); it++)
      it->clear();
  }

  int		Input::getAxis(unsigned int axis, unsigned int joystick) const
  {
    if (joystick < _joysticks.size())
      return (_joysticks.at(joystick).getAxis(axis));
    return (0);
  }

  int		Input::getAxisDelta(unsigned int axis, unsigned int joystick) const
  {
    if (joystick < _joysticks.size())
      return (_joysticks.at(joystick).getAxisDelta(axis));
    return (0);
  }

  bool		Input::getButton(unsigned int button, unsigned int joystick) const
  {
    if (joystick < _joysticks.size())
      return (_joysticks.at(joystick).getButton(button));
    return (false);
  }

  bool		Input::getButtonDown(unsigned int button, unsigned int joystick) const
  {
    if (joystick < _joysticks.size())
      return (_joysticks.at(joystick).getButtonDown(button));
    return (false);
  }

  bool		Input::getButtonUp(unsigned int button, unsigned int joystick) const
  {
    if (joystick < _joysticks.size())
      return (_joysticks.at(joystick).getButtonUp(button));
    return (false);
  }

  int		Input::getJoystickNum() const
  {
    return (_joysticks.size());
  }

  bool		Input::getKey(unsigned int key) const
  {
    if (std::find(_activeKeys.begin(), _activeKeys.end(), key) != _activeKeys.end())
      return (true);
    return (false);
  }

  bool		Input::getKeyDown(unsigned int key) const
  {
    if (std::find(_pressedKeys.begin(), _pressedKeys.end(), key) != _pressedKeys.end())
      return (true);
    return (false);
  }

  bool		Input::getKeyUp(unsigned int key) const
  {
    if (std::find(_releasedKeys.begin(), _releasedKeys.end(), key) != _releasedKeys.end())
      return (true);
    return (false);
  }

  bool		Input::getMouseButton(unsigned int button) const
  {
    if (std::find(_activeMouseButtons.begin(), _activeMouseButtons.end(), button) != _activeMouseButtons.end())
      return (true);
    return (false);
  }

  bool		Input::getMouseButtonDown(unsigned int button) const
  {
    if (std::find(_activeMouseButtons.begin(), _activeMouseButtons.end(), button) != _releasedMouseButtons.end())
      return (true);
    return (false);
  }

  bool		Input::getMouseButtonUp(unsigned int button) const
  {
    if (std::find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), button) != _pressedMouseButtons.end())
      return (true);
    return (false);
  }

  glm::ivec2	Input::getCursorPosition() const
  {
    return (_cursorPosition);
  }

  glm::ivec2	Input::getCursorDelta() const
  {
    return (_cursorDelta);
  }

  glm::ivec2	Input::getWheelDelta() const
  {
    return (_wheelDelta);
  }

  bool		Input::getEvent(unsigned int event) const
  {
    if (std::find(_events.begin(), _events.end(), event) != _events.end())
      return (true);
    return (false);
  }

  void		Input::onPressedKey(const SDL_Event& event)
  {
    if (event.key.repeat)
      return;
    if (std::find(_activeKeys.begin(), _activeKeys.end(), event.key.keysym.sym) == _activeKeys.end())
      _activeKeys.push_back(event.key.keysym.sym);
    if (std::find(_pressedKeys.begin(), _pressedKeys.end(), event.key.keysym.sym) == _pressedKeys.end())
      _pressedKeys.push_back(event.key.keysym.sym);
  }

  void		Input::onReleasedKey(const SDL_Event& event)
  {
    EventListIt	it;

    if ((it = std::find(_activeKeys.begin(), _activeKeys.end(), event.key.keysym.sym)) != _activeKeys.end())
      _activeKeys.erase(it);
    if (std::find(_releasedKeys.begin(), _releasedKeys.end(), event.key.keysym.sym) == _releasedKeys.end())
      _releasedKeys.push_back(event.key.keysym.sym);
  }

  void		Input::onPressedMouseButton(const SDL_Event& event)
  {
    if (std::find(_activeMouseButtons.begin(), _activeMouseButtons.end(), event.button.button) == _activeMouseButtons.end())
      _activeMouseButtons.push_back(event.button.button);
    if (std::find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), event.button.button) == _pressedMouseButtons.end())
      _pressedMouseButtons.push_back(event.button.button);
  }

  void		Input::onReleasedMouseButton(const SDL_Event& event)
  {
    EventListIt	it;

    if ((it = std::find(_activeMouseButtons.begin(), _activeMouseButtons.end(), event.button.button)) != _activeMouseButtons.end())
      _activeMouseButtons.erase(it);
    if (std::find(_releasedMouseButtons.begin(), _releasedMouseButtons.end(), event.button.button) == _releasedMouseButtons.end())
      _releasedMouseButtons.push_back(event.button.button);
  }

  void		Input::onMouseMotion(const SDL_Event& event)
  {
    _cursorPosition = glm::ivec2(event.motion.x, event.motion.y);
    _cursorDelta += glm::ivec2(event.motion.xrel, event.motion.yrel);
  }

  void		Input::onWheelMotion(const SDL_Event& event)
  {
    _wheelDelta += glm::ivec2(event.wheel.x, event.wheel.y);
  }

  void		Input::onAxisMotion(const SDL_Event& event)
  {
    if (static_cast<unsigned>(event.jaxis.which) >= _joysticks.size())
      return;
    _joysticks[event.jaxis.which].onAxisMotion(event);
  }

  void		Input::onPressedButton(const SDL_Event& event)
  {
    if (static_cast<unsigned>(event.jaxis.which) >= _joysticks.size())
      return;
    _joysticks[event.jaxis.which].onPressedButton(event);
  }

  void		Input::onReleasedButton(const SDL_Event& event)
  {
    if (static_cast<unsigned>(event.jaxis.which) >= _joysticks.size())
      return;
    _joysticks[event.jaxis.which].onReleasedButton(event);
  }

  void		Input::onUnknownEvent(const SDL_Event& event)
  {
    if (std::find(_events.begin(), _events.end(), event.type) == _events.end())
      _events.push_back(event.type);
  }
};
