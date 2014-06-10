#include "game/GameLoadingState.hh"
#include "game/GameManager.hh"
#include "game/GameState.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/Object.hh"
#include "graphic/Camera.hh"
#include "graphic/RenderState.hh"
#include "graphic/ProjectionPerspective.hh"
#include "graphic/Screen.hh"
#include "sound/SoundManager.hh"
#include "events/Input.hh"

namespace bbm
{
  GameLoadingState::GameLoadingState(GameManager& gameManager) :
    _manager(gameManager)
  {
    _finish = false;
    TextureManager::getInstance()->addTexture("load", "assets/game/Loading.tga");
    TextureManager::getInstance()->addTexture("load2", "assets/game/LoadingFinish.tga");

    _loading = new Object("load", "default", GL_QUADS);
    _loading->pushVertex(glm::vec3(0, 0, 0));
    _loading->pushVertex(glm::vec3(0, 1, 0));
    _loading->pushVertex(glm::vec3(1, 1, 0));
    _loading->pushVertex(glm::vec3(1, 0, 0));

    _loading->pushUv(glm::vec2(0, 0));
    _loading->pushUv(glm::vec2(0, 1));
    _loading->pushUv(glm::vec2(1, 1));
    _loading->pushUv(glm::vec2(1, 0));

    _loadingFinished = new Object("load", "default", GL_QUADS);
    _loadingFinished->pushVertex(glm::vec3(0, 0, 0));
    _loadingFinished->pushVertex(glm::vec3(0, 1, 0));
    _loadingFinished->pushVertex(glm::vec3(1, 1, 0));
    _loadingFinished->pushVertex(glm::vec3(1, 0, 0));

    _loadingFinished->pushUv(glm::vec2(0, 0));
    _loadingFinished->pushUv(glm::vec2(0, 1));
    _loadingFinished->pushUv(glm::vec2(1, 1));
    _loadingFinished->pushUv(glm::vec2(1, 0));


    loadShader();
    loadTexture();
    loadSound();
    loadModel();
    _finish = true;
  }

  GameLoadingState::~GameLoadingState()
  {
  }

  void			GameLoadingState::loadShader()
  {
    ShaderManager::getInstance()->addShader("default", "gdl/shaders/basic.vp",
					    "gdl/shaders/basic.fp");
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
    if (input.getKeyDown(SDLK_ESCAPE))
      {
	GameState*		state = new GameState(_manager);
	Serializer		s = Serializer::create<JSONSerializer>();

	try
	  {
	    s->deserializeFromFile("save1.json", *state);
	    // s->serializeToFile("export1.json", *state);
	  }
	catch (SerializerException& ex)
	  {
	    std::cout << "Serializer GameState Error : " << ex.what() << std::endl;
	  }
	_manager.push(state);
      }
  }

  void			GameLoadingState::draw(float time, Screen& context)
  {
    Transform		cam = Camera(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    Transform		projection = ProjectionPerspective(60, 512 / 384, 1, 1000);

    if (!_finish)
      context.draw(*_loading, RenderState(projection, cam));
    else
      context.draw(*_loadingFinished, RenderState(projection, cam));
  }

  void			GameLoadingState::revealing()
  {
  }
};
