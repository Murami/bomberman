#include <iostream>
#include <algorithm>
#include "events/Joystick.hh"

namespace bbm
{
  Joystick::Joystick(int i)
  {
    std::cout << "Joystick " << i << " created" << std::endl;
    _joystickSDL = SDL_JoystickOpen(i);
    _axes.resize(SDL_JoystickNumAxes(_joystickSDL));
    std::cout << "Axes found : " << SDL_JoystickNumAxes(_joystickSDL) << std::endl;
    for (int i = 0; i < SDL_JoystickNumAxes(_joystickSDL); i++)
      {
	_axes[i]._lastPosition = 0;
	_axes[i]._position = 0;
      }
  }

  Joystick::~Joystick()
  {
  }

  void	Joystick::clear()
  {
    AxesListIt	it;

    _pressedButtons.clear();
    _releasedButtons.clear();
    for (it = _axes.begin(); it != _axes.end(); it++)
      (*it)._lastPosition = (*it)._position;
  }

  int	Joystick::getAxis(unsigned int axis) const
  {
    if (axis < _axes.size())
      return (_axes.at(axis)._position);
    return (0);
  }

  int	Joystick::getAxisDelta(unsigned int axis) const
  {
    if (axis < _axes.size())
      return (_axes.at(axis)._lastPosition - _axes[axis]._position);
    return (0);
  }

  bool	Joystick::getButton(unsigned int button) const
  {
    if (std::find(_activeButtons.begin(), _activeButtons.end(), button) != _activeButtons.end())
      return (true);
    return (false);
  }

  bool	Joystick::getButtonDown(unsigned int button) const
  {
    if (std::find(_pressedButtons.begin(), _pressedButtons.end(), button) != _pressedButtons.end())
      return (true);
    return (false);
  }

  bool	Joystick::getButtonUp(unsigned int button) const
  {
    if (std::find(_releasedButtons.begin(), _releasedButtons.end(), button) != _releasedButtons.end())
      return (true);
    return (false);
  }

  void	Joystick::onAxisMotion(const SDL_Event& event)
  {
    if (event.jaxis.axis < _axes.size())
      _axes[event.jaxis.axis]._position = event.jaxis.value;
  }

  void	Joystick::onPressedButton(const SDL_Event& event)
  {
    if (std::find(_activeButtons.begin(), _activeButtons.end(), event.jbutton.button) == _activeButtons.end())
      _activeButtons.push_back(event.jbutton.button);
    if (std::find(_pressedButtons.begin(), _pressedButtons.end(), event.jbutton.button) == _pressedButtons.end())
      _pressedButtons.push_back(event.jbutton.button);
  }

  void	Joystick::onReleasedButton(const SDL_Event& event)
  {
    EventIt	it;

    std::cout << "pressed button " << (int)event.jbutton.button << " !" << std::endl;
    if ((it = std::find(_activeButtons.begin(), _activeButtons.end(), event.jbutton.button)) != _activeButtons.end())
      _activeButtons.erase(it);
    if (std::find(_releasedButtons.begin(), _releasedButtons.end(), event.jbutton.button) == _releasedButtons.end())
      _releasedButtons.push_back(event.jbutton.button);
  }
};
