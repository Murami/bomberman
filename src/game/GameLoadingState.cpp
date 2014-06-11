#include "game/GameLoadingState.hh"
#include "game/GameManager.hh"
#include "game/GameState.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/Object.hh"
#include "graphic/Camera.hh"
#include "graphic/RenderState.hh"
#include "graphic/ProjectionPerspective.hh"
#include "graphic/Screen.hh"
#include "sound/SoundManager.hh"
#include "events/Input.hh"

const float scaleFactor = 1.0;

namespace bbm
{
  GameLoadingState::GameLoadingState(GameManager& gameManager,
				     GameConfig* config) :
    _manager(gameManager),
    _config(config)
  {
    TextureManager::getInstance()->addTexture("load", "assets/game/Loading.tga");
    TextureManager::getInstance()->addTexture("load2", "assets/game/LoadingFinish.tga");

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
    SoundManager::getInstance()->addSound("menu", "assets/sound/Turning_tables.mp3");
    SoundManager::getInstance()->addSound("banzai", "assets/sound/banzai.mp3");
  }

  void			GameLoadingState::loadModel()
  {
    Marvin::initialize();
  }

  void			GameLoadingState::loadGameState()
  {
    GameState*			state;
    PlayerConfig		playerConfig;
    GameState::GameStateConfig	gameStateConfig;

    if (_config->player1)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load("inputConfig1.json");
	playerConfig.splitScreenPosition = glm::vec2(0, 0);
	playerConfig.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player2)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load("inputConfig2.json");
	playerConfig.splitScreenPosition = glm::vec2(512 * 1.5, 0);
	playerConfig.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player3)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load("inputConfig3.json");
	playerConfig.splitScreenPosition = glm::vec2(0, 384 * 1.5);
	playerConfig.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    if (_config->player4)
      {
	playerConfig.inputConfig = new InputConfig;
	playerConfig.inputConfig->load("inputConfig4.json");
	playerConfig.splitScreenPosition = glm::vec2(512 * 1.5, 384 * 1.5);
	playerConfig.splitScreenSize = glm::vec2(512 * 1.5, 384 * 1.5);
	gameStateConfig.playersConfigs.push_back(playerConfig);
      }
    state = new GameState(_manager, &gameStateConfig);
    state->load("save1.json");
    _manager.push(state);
  }

  void			GameLoadingState::initialize()
  {
  }

  void			GameLoadingState::release()
  {
    Marvin::release();
  }

  void			GameLoadingState::obscuring()
  {
  }

  void			GameLoadingState::update(float time, const Input& input)
  {
    if (!_finish)
      {
	loadShader();
	loadTexture();
	loadSound();
	loadModel();
	_finish = true;
      }
    else if (input.getKeyDown(SDLK_SPACE))
      {
	loadGameState();
      }
  }

  void			GameLoadingState::draw(float time, Screen& context)
  {
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