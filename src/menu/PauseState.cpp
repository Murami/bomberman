#include		"game/GameManager.hh"
#include		"PauseState.hh"

namespace		bbm
{
  const std::string	PauseState::PAUSE_BACKGROUND =
    "./assets/menu/images/grimmnight.tga";

  PauseState::PauseState(GameManager& manager, GameState* state) :
    _manager(manager), _gameState(state)
  {
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
  }

  void		PauseState::initialize()
  {
    this->_image = new Image(PAUSE_BACKGROUND);
    if (!this->_image->initialize())
      throw (FileLoadingException(PAUSE_BACKGROUND));
    this->_image->scale(glm::vec3(10, 10, 10));
  }

  void		PauseState::release()
  {
  }

  void		PauseState::obscuring()
  {
  }

  void		PauseState::update(float time, const Input& input)
  {
    (void) time;
    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	_manager.pop();
      }
  }

  void		PauseState::draw(float time, Screen& context)
  {
    Transform	perspective = ProjectionPerspective(60,
						    context.getSize().x /
						    context.getSize().y, 1.0f,
						    1000.0f);
    Transform	camera = Camera(glm::vec3(10, 0, 0),
				glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    RenderState	state(perspective, camera);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x,
					       context.getSize().y));
    context.clear();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.25f);
    context.draw(*this->_image, state);
    //this->_gameState->draw(time, context);
    context.flush();
  }

  void		PauseState::revealing()
  {
  }

  void		PauseState::setPlayMenu(Menu*)
  {
  }

  void		PauseState::setOptionsMenu(Menu*)
  {
  }

  void		PauseState::setHighScoreMenu(Menu*)
  {
  }

  void		PauseState::exitGame(Menu*)
  {
  }

  void		PauseState::setNewGameMenu(Menu*)
  {
  }

  void		PauseState::setContinueGameMenu(Menu*)
  {
  }

  void		PauseState::setLoadGameMenu(Menu*)
  {
  }

  void		PauseState::setMainMenu(Menu*)
  {
  }

  void		PauseState::setOptionsAudioMenu(Menu*)
  {
  }

  void		PauseState::setOptionsControlMenu(Menu*)
  {
  }

  void		PauseState::setNextFrame(Menu*)
  {
  }

  void		PauseState::setPrevFrame(Menu*)
  {
  }

  void		PauseState::setIASelectionMenu(Menu*)
  {
  }

  void		PauseState::launchLoadedGame(Menu*)
  {
  }

  void		PauseState::launchNewGame(Menu*)
  {
  }

  void		PauseState::setOptionControlPlayer1(Menu*)
  {
  }

  void		PauseState::setOptionControlPlayer2(Menu*)
  {
  }

  void		PauseState::setOptionControlPlayer3(Menu*)
  {
  }

  void		PauseState::setOptionControlPlayer4(Menu*)
  {
  }

  void		PauseState::setMapParamsMenu(Menu*)
  {
  }

  void		PauseState::serializeBindingPlayer1(Menu*)
  {
  }

  void		PauseState::serializeBindingPlayer2(Menu*)
  {
  }

  void		PauseState::serializeBindingPlayer3(Menu*)
  {
  }

  void		PauseState::serializeBindingPlayer4(Menu*)
  {
  }

  void		PauseState::serializeAudioSettings(Menu*)
  {
  }

  PauseState::~PauseState()
  {
  }
}
