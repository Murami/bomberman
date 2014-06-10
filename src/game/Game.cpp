#include <ctime>
#include <cstdlib>
#include "game/Game.hh"
#include "game/GameState.hh"
#include "game/FrameManager.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "menu/MenuState.hh"
#include "menu/PauseState.hh"
#include "sound/SoundManager.hh"

namespace bbm
{
  /// !! FICHIER DE CONFIG POUR LA RESOLUTION
  Game::Game() :
    _screen(glm::vec2(1024 * 1.5, 768 * 1.5), "Bomberman")
  {
    std::srand(std::time(0));
    // A PAS FAIRE ICI MAIS DANS UN GAME STATE LOADING !!!!
    ShaderManager::getInstance()->addShader("default", "gdl/shaders/basic.vp",
					    "gdl/shaders/basic.fp");
    TextureManager::getInstance()->addTexture("fire",
					      "assets/game/effects/fire.tga");
    TextureManager::getInstance()->addTexture("dark",
					      "assets/game/effects/dark.tga");
    TextureManager::getInstance()->addTexture("water",
					      "assets/game/effects/water.tga");

    TextureManager::getInstance()->addTexture("wall", "assets/game/box/wall.tga");
    TextureManager::getInstance()->addTexture("gamebox", "assets/game/box/gamebox.tga");

    TextureManager::getInstance()->addTexture("ground", "assets/game/metal4.tga");

    TextureManager::getInstance()->addTexture("fireBonus",
					      "assets/game/bonus/fire_bonus.tga");
    TextureManager::getInstance()->addTexture("bombBonus",
					      "assets/game/bonus/bomb_bonus.tga");
    TextureManager::getInstance()->addTexture("speedBonus",
					      "assets/game/bonus/speed_bonus.tga");
    TextureManager::getInstance()->addTexture("darkBonus",
					      "assets/game/bonus/dark_bonus.tga");
    TextureManager::getInstance()->addTexture("boxBonus",
					      "assets/game/bonus/box_bonus.tga");
    TextureManager::getInstance()->addTexture("waterBonus",
					      "assets/game/bonus/water_bonus.tga");
    TextureManager::getInstance()->addTexture("deathBonus",
					      "assets/game/bonus/death_bonus.tga");
    TextureManager::getInstance()->addTexture("randomBonus",
					      "assets/game/bonus/random_bonus.tga");
    TextureManager::getInstance()->addTexture("powerBonus",
					      "assets/game/bonus/power_bonus.tga");
    TextureManager::getInstance()->addTexture("randomBonus",
					      "assets/game/bonus/random_bonus.tga");

    SoundManager::getInstance()->addSound("banzai", "assets/sound/plufort.mp3");
  }

  Game::~Game()
  {
  }

  int	Game::run()
  {
    FrameManager	frame(60);
    IGameState*		state = new MenuState(_manager);

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
