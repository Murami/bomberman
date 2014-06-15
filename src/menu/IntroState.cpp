#include		"menu/IntroState.hh"
#include		"menu/IntroMarvin.hh"

#include		"events/Input.hh"

#include		"graphic/Screen.hh"
#include		"graphic/ProjectionPerspective.hh"
#include		"graphic/Camera.hh"
#include		"graphic/RenderState.hh"
#include		"graphic/ModelManager.hh"
#include		"sound/SoundManager.hh"


namespace		bbm
{
  const std::string	IntroState::SCREEN_PATH = "./assets/intro/screen.tga";

  IntroState::IntroState(GameManager& manager) :
    _manager(manager)
  {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    this->_screen = new Image(SCREEN_PATH);
    SoundManager::getInstance()->addMusic("menu", "assets/sound/heart_of_courage.mp3");
  }

  void		IntroState::initialize()
  {
    this->_skybox.initialize();
    ModelManager::getInstance()->addModel("introbomberman",
					  "./assets/intro/bomberman.fbx");
    this->_marvin = new IntroMarvin();
    this->_screen->initialize();
    this->_screen->rotate(glm::vec3(0, 1, 0), 180);
    this->_screen->scale(glm::vec3(0, 6, 11));
  }

  void		IntroState::release()
  {
  }

  void		IntroState::obscuring()
  {
  }

  void		IntroState::update(float time, const Input& input)
  {
    if (input.getKeyDown(SDLK_ESCAPE) || input.getKeyDown(SDLK_SPACE))
      {
	SoundManager::getInstance()->play("menu");
	this->_manager.pop();
      }
    this->_marvin->update(time);
    this->_skybox.update();
  }

  void		IntroState::draw(float, Screen& context)
  {
    static int i = 0;
    static int x = 3;
    static int y = 8;
    static int z = 10;
    static int fov = 60;
    Transform	perspective = ProjectionPerspective(fov, context.getSize().x /
						    context.getSize().y, 0.1f,
						    1000);
    Transform camera;
    camera = Camera(glm::vec3(x, y, z),
		    glm::vec3(0, 3, 0), glm::vec3(0, 1, 0));
    if (i >= 66)
      {
	if (x > 0)
	  x--;
	if (z > 1)
	  z--;
	if (fov > 0 && z == 1 && x == 0)
	  fov--;
      }
    RenderState	state(perspective, camera);

    context.clear();
    context.draw(*this->_marvin, state);
    if (fov == 0)
      context.draw(*this->_screen, state);
    perspective = ProjectionPerspective(60, context.getSize().x /
					context.getSize().y, 0.1f,
					1000);
    camera = Camera(glm::vec3(10, 0, 0),
				glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    state = RenderState(perspective, camera);
    context.draw(this->_skybox, state);
    if (fov == 0)
      context.draw(*this->_screen, state);
    context.flush();
    i++;
  }

  void		IntroState::revealing()
  {
  }

  IntroState::~IntroState()
  {
  }

}
