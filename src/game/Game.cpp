//
// Game.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:28:16 2014 otoshigami
// Last update Sun Jun 15 12:58:27 2014 otoshigami
//

#include <ctime>
#include <cstdlib>
#include "game/Game.hh"
#include "game/GameState.hh"
#include "game/FrameManager.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "menu/MenuState.hh"
#include "menu/PauseState.hh"
#include "menu/IntroState.hh"
#include "sound/SoundManager.hh"

namespace bbm
{
  Game::Game() :
    _screen("Bomberman")
  {
    std::srand(std::time(0));
    ShaderManager::getInstance()->addShader("default", "gdl/shaders/basic.vp",
					    "gdl/shaders/basic.fp");
    ShaderManager::getInstance()->addShader("default2", "gdl/shaders/basic.vp",
					    "gdl/shaders/basic2.fp");

  }

  Game::~Game()
  {
  }

  int	Game::run()
  {
    FrameManager	frame(60);
    IGameState*		introState = new IntroState(_manager);
    IGameState*		menuState = new MenuState(_manager);
    _manager.push(menuState);
    _manager.push(introState);

    frame.start();
    while (_manager.top())
      {
	_input.update();
	_manager.update(frame.getTime(), _input);
	if (_manager.top())
	  _manager.draw(frame.getTime(), _screen);
	frame.update();
      }

    delete introState;
    delete menuState;
    return (0);
  }
};
