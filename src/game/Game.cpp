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
  /// !! FICHIER DE CONFIG POUR LA RESOLUTION
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
    IGameState*		state = new MenuState(_manager);
    _manager.push(state);
    state = new IntroState(_manager);
    // IGameState*		state = new PauseState(_manager, NULL);

    _manager.push(state);

    SoundManager::getInstance()->play("banzai");
    frame.start();
    while (_manager.top())
      {
	_input.update();
	_manager.update(frame.getTime(), _input);
	if (_manager.top())
	  _manager.draw(frame.getTime(), _screen);
	frame.update();
      }

    delete state;
    return (0);
  }
};
