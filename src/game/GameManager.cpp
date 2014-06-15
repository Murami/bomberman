//
// GameManager.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:28:34 2014 otoshigami
// Last update Sun Jun 15 08:28:35 2014 otoshigami
//

#include <cstdlib>
#include "game/GameManager.hh"
#include "game/IGameState.hh"
#include "graphic/Screen.hh"

namespace bbm
{
  GameManager::GameManager()
  {
  }

  GameManager::~GameManager()
  {
  }

  void		GameManager::set(IGameState* state)
  {
    if (!_states.empty())
      {
	_states.back()->release();
	_states.pop_back();
	state->initialize();
	_states.push_back(state);
      }
  }

  void		GameManager::push(IGameState* state)
  {
    if (!_states.empty())
      _states.back()->obscuring();
    _states.push_back(state);
    state->initialize();
  }

  void		GameManager::pop()
  {
    IGameState*	state;

    if (!_states.empty())
      {
	state = _states.back();
	state->release();
	_states.pop_back();
	if (!_states.empty())
	  _states.back()->revealing();
      }
  }

  IGameState*	GameManager::top()
  {
    if (!_states.empty())
      return (_states.back());
    return (NULL);
  }

  void		GameManager::update(float time, const Input& input)
  {
    if (top())
      top()->update(time, input);
  }

  void		GameManager::draw(float time, Screen& screen)
  {
    if (top())
      top()->draw(time, screen);
  }
};
