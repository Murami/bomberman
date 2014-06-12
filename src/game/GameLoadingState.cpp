#include <string>
#include "game/GameLoadingState.hh"
#include "game/GameManager.hh"
#include "game/GameState.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/ModelManager.hh"
#include "graphic/Object.hh"
#include "graphic/Camera.hh"
#include "graphic/RenderState.hh"
#include "graphic/ProjectionPerspective.hh"
#include "graphic/Screen.hh"
#include "sound/SoundManager.hh"
#include "events/Input.hh"
# include "MenuState.hh"

const float scaleFactor = 1.0;

namespace bbm
{
  GameLoadingState::GameLoadingState(GameManager& gameManager,
				     GameConfig* config) :
    _manager(gameManager),
    _config(config)
  {
    try
      {
	TextureManager::getInstance()->addTexture("load", "assets/game/Loading.tga");
	TextureManager::getInstance()->addTexture("load2", "assets/game/LoadingFinish.tga");
      }
    catch (const std::exception& e)
      {
	TextureManager::getInstance()->delTexture("load");
	TextureManager::getInstance()->delTexture("load2");
	std::cout << e.what() << std::endl;
	_manager.pop();
	return;
      }

    _loading = new Object("load", "default", GL_QUADS);
    _loading->pushVertex(glm::vec3(-0.5, -0.5, 0));
    _loading->pushVertex(glm::vec3(-0.5, 0.5, 0));
    _loading->pushVertex(glm::vec3(0.5, 0.5, 0));
    _loading->pushVertex(glm::vec3(0.5, -0.5, 0));

    _loading->pushUv(glm::vec2(0, 0));
    _loading->pushUv(glm::vec2(0, 1));
    _loading->pushUv(glm::vec2(1, 1));
    _loading->pushUv(glm::vec2(1, 0));

    _loadingFinished = new Object("load2", "default", GL_QUADS);
    _loadingFinished->pushVertex(glm::vec3(-0.5, -0.5, 0));
    _loadingFinished->pushVertex(glm::vec3(-0.5, 0.5, 0));
    _loadingFinished->pushVertex(glm::vec3(0.5, 0.5, 0));
    _loadingFinished->pushVertex(glm::vec3(0.5, -0.5, 0));

    _loadingFinished->pushUv(glm::vec2(0, 0));
    _loadingFinished->pushUv(glm::vec2(0, 1));
    _loadingFinished->pushUv(glm::vec2(1, 1));
    _loadingFinished->pushUv(glm::vec2(1, 0));

    _loadingFinished->build();
    _loading->build();
    _loading->scale(glm::vec3(scaleFactor, scaleFactor, 0));
    _loadingFinished->scale(glm::vec3(scaleFactor, scaleFactor, 0));

    _finish = false;
  }

  GameLoadingState::~GameLoadingState()
  {
  }

  void			GameLoadingState::loadShader()
  {
  }

  void			GameLoadingState::loadTexture()
  {
    TextureManager::getInstance()->addTexture("fire", "assets/game/effects/fire.tga");
    TextureManager::getInstance()->addTexture("dark", "assets/game/effects/dark.tga");
    TextureManager::getInstance()->addTexture("water", "assets/game/effects/water.tga");
    TextureManager::getInstance()->addTexture("wall", "assets/game/box/wall.tga");
    TextureManager::getInstance()->addTexture("gamebox", "assets/game/box/gamebox.tga");
    TextureManager::getInstance()->addTexture("ground", "assets/game/metal4.tga");
    TextureManager::getInstance()->addTexture("fireBonus", "assets/game/bonus/fire_bonus.tga");
    TextureManager::getInstance()->addTexture("bombBonus", "assets/game/bonus/bomb_bonus.tga");
    TextureManager::getInstance()->addTexture("speedBonus", "assets/game/bonus/speed_bonus.tga");
    TextureManager::getInstance()->addTexture("darkBonus", "assets/game/bonus/dark_bonus.tga");
    TextureManager::getInstance()->addTexture("boxBonus", "assets/game/bonus/box_bonus.tga");
    TextureManager::getInstance()->addTexture("waterBonus", "assets/game/bonus/water_bonus.tga");
    TextureManager::getInstance()->addTexture("deathBonus", "assets/game/bonus/death_bonus.tga");
    TextureManager::getInstance()->addTexture("randomBonus", "assets/game/bonus/random_bonus.tga");
    TextureManager::getInstance()->addTexture("powerBonus", "assets/game/bonus/power_bonus.tga");
    TextureManager::getInstance()->addTexture("randomBonus", "assets/game/bonus/random_bonus.tga");
  }

  void			GameLoadingState::loadSound()
  {
    SoundManager::getInstance()->addMusic("menu", "assets/sound/Turning_tables.mp3");
    SoundManager::getInstance()->addMusic("theme", "assets/sound/bomberman_them.mp3");
    SoundManager::getInstance()->addSound("banzai", "assets/sound/banzai.mp3");
    SoundManager::getInstance()->addSound("aquaBomb", "assets/sound/aqua_bomb.mp3");
    SoundManager::getInstance()->addSound("bomb", "assets/sound/Bomb_Blow.wav");
    SoundManager::getInstance()->addSound("bigBomb", "assets/sound/big_bomb.mp3");
  }

  void			GameLoadingState::loadModel()
  {
    Marvin::initialize();
    Wall::initialize();
    ModelManager::getInstance()->addModel("FireBomb",
					    "assets/models_bomb/FireBomb/Bomb.obj");
    ModelManager::getInstance()->addModel("WaterBomb",
					    "assets/models_bomb/AquaBomb/AquaBomb.obj");
    ModelManager::getInstance()->addModel("PowerBomb",
					    "assets/models_bomb/PowerBomb2/Bomb.obj");
    ModelManager::getInstance()->addModel("DarkBomb",
					    "assets/models_bomb/DarkBomb/Bomb.obj");
    ModelManager::getInstance()->addModel("BoxBomb",
					    "assets/models_bomb/LightBomb/LightBomb.obj");
    ModelManager::getInstance()->addModel("MultiBomb",
					    "assets/models_bomb/WindBomb/WindBomb.obj");
  }

  void			GameLoadingState::newGameState()
  {
    std::cout << "new" << std::endl;
    GameState*			state;
    PlayerConfig		playerConfig;
    GameState::GameStateConfig	gameStateConfig;

    playerConfig.power = 3;
    playerConfig.typeBomb = FIRE;
    playerConfig.nbBombs = 1;
    playerConfig.nbBombsBonus = 1;
    playerConfig.speed = 0.005;
    playerConfig.state = IDLE;
    playerConfig.alive = true;
    playerConfig.slow = false;
    playerConfig.dark = false;
    playerConfig.position = glm::vec2(5, 5);
    if (_config->player1)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load(MenuState::INPUT_CONFIG_P1);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player2)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load(MenuState::INPUT_CONFIG_P2);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player3)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load(MenuState::INPUT_CONFIG_P3);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player4)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load(MenuState::INPUT_CONFIG_P4);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    state = new GameState(_manager, &gameStateConfig);
    state->randomize(_config->mapSizeX, _config->mapSizeY);
    _manager.push(state);
  }

  void                  GameLoadingState::loadGameState()
  {
    std::cout << "load" << std::endl;
    GameState*			state;
    GameState::GameStateConfig	gameStateConfig;


    state = new GameState(_manager, &gameStateConfig);
    state->load(*(_config->fileToLoad));
    _manager.push(state);
  }

  void			GameLoadingState::initialize()
  {
  }

  void			GameLoadingState::release()
  {
    Marvin::release();
    Wall::release();
  }

  void			GameLoadingState::obscuring()
  {
  }

  void			GameLoadingState::update(float time, const Input& input)
  {
    (void) time;
    if (!_finish)
      {
	try
	  {
	    loadShader();
	    loadTexture();
	    loadSound();
	    loadModel();
	  }
	catch (const std::exception& e)
	  {
	    std::cout << e.what() << std::endl;
	    _manager.pop();
	  }
	_finish = true;
      }
    else if (input.getKeyDown(SDLK_SPACE))
      {
	if (_config->newGame == true)
	  newGameState();
	else
	  loadGameState();
      }
  }

  void			GameLoadingState::draw(float time, Screen& context)
  {
    (void) time;
    Transform		cam = Camera(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    Transform		projection = ProjectionPerspective(60, 1600 / 900, 1, 1000);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();
    if (!_finish)
      context.draw(*_loading, RenderState(projection, cam));
    else
      context.draw(*_loadingFinished, RenderState(projection, cam));
    context.flush();
  }

  void			GameLoadingState::revealing()
  {
    _manager.pop();
  }
};
