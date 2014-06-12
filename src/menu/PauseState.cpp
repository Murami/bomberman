#include		"game/GameManager.hh"
#include		"PauseState.hh"

namespace		bbm
{
  const std::string	PauseState::PAUSE_BACKGROUND =
    "./assets/menu/images/violentdays.tga";

  PauseState::PauseState(GameManager& manager, GameState* state) :
    _manager(manager), _gameState(state)
  {
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
  }

  void		PauseState::_setNewCurrentMenu(const std::string& name)
  {
    std::list<Menu*>::iterator it = this->_menuList.begin();
    while (it != this->_menuList.end())
      {
	if ((*it)->getTitle() == name)
	  {
	    this->_currentMenu = (*it);
	    this->_currentMenu->initialize();
	    return ;
	  }
	it++;
      }
    std::cerr << "Setting new menu : \'" << name << "\' : not found"
	      << std::endl;
  }

  bool		PauseState::_initializePauseMainMenu()
  {
    Menu* menu = new Menu("pausemainmenu", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("resume", &IMenuManager::resumeGame,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("save", NULL, glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("options", NULL, glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("quit", NULL, glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_currentMenu = menu;
  }

  void		PauseState::initialize()
  {
    this->_image = new Image(PAUSE_BACKGROUND);
    if (!this->_image->initialize())
      throw (FileLoadingException(PAUSE_BACKGROUND));
    this->_image->scale(glm::vec3(25, 25, 25));
    this->_image->translate(glm::vec3(-10, 0, 0));
    this->_initializePauseMainMenu();
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
    this->_currentMenu->update(input);
  }

  void		PauseState::draw(float, Screen& context)
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
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glAlphaFunc(GL_GREATER, 0.25f);
    context.draw(*this->_image, state);
    //this->_gameState->draw(time, context);
    context.draw(*this->_currentMenu, state);
    context.flush();
  }

  void		PauseState::revealing()
  {
  }

  void		PauseState::resumeGame(Menu*)
  {
    this->_manager.pop();
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
