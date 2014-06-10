#include "game/GameLoadingState.hh"
#include "game/GameManager.hh"
#include "game/GameState.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "sound/SoundManager.hh"
#include "events/Input.hh"

namespace bbm
{
  GameLoadingState::GameLoadingState(GameManager& gameManager) :  _manager(gameManager)
  {
    loadShader();
    loadTexture();
    loadSound();
    loadModel();
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
  }

  void			GameLoadingState::revealing()
  {
  }
};
