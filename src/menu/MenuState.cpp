#include		"FileExplorer.hh"
#include		"events/Input.hh"
#include		"game/GameManager.hh"
#include		"graphic/Screen.hh"
#include		"graphic/Camera.hh"
#include		"graphic/ProjectionPerspective.hh"
#include		"MenuState.hh"

#include		"serializer/ISerializedNode.hh"
#include		"serializer/JSONSerializer.hh"
#include		"serializer/Serializer.hh"
#include		"serializer/SerializerException.hh"

namespace	bbm
{
  MenuState::MenuState(GameManager& manager) : _manager(manager)
  {
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
  }

  bool		MenuState::_initializeMainMenu()
  {
    Menu* menu = new Menu("bomberman", this);
    if (!menu->initialize())
      return (false);
    menu->createNewButton("play", &IMenuManager::setPlayMenu,
    			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("options", &IMenuManager::setOptionsMenu,
    			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("highscores", &IMenuManager::setHighScoreMenu,
    			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("quit", &IMenuManager::exitGame,
    			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_currentMenu = menu;
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeLoadGameMenu()
  {
    Menu* menu = new Menu("loadcampaign", this);
    if (!menu->initialize())
      return (false);
    menu->createNewButton("next", &IMenuManager::setNextFrame,
  			  glm::vec4(1, 1, 1, 1), false);
    menu->createNewButton("prev", &IMenuManager::setPrevFrame,
  			  glm::vec4(1, 1, 1, 1), false);

    ///////////////////////////////////////////////
    // CHANGER LAUNCHNEWGAME EN LAUNCHLOADEDGAME //
    ///////////////////////////////////////////////

    menu->createNewButton("play", &IMenuManager::launchNewGame,
  			  glm::vec4(0, 1, 0, 1), false);
    menu->createNewButton("back", &IMenuManager::setPlayMenu,
  			  glm::vec4(1, 0, 0, 1), true);
    menu->createFrame();
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeIASelection4Menu()
  {
    Menu* menu = new Menu("iaselection4", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("lvl ia 4", NULL, 3,
    			       glm::vec4(1, 0, 1, 1), "easy");
    menu->addStateToLastButton("medium");
    menu->addStateToLastButton("hard");
    menu->createNewStateButton("nb ia", NULL, 6,
			       glm::vec4(1, 0, 1, 1), "0");
    menu->addStateToLastButton("1");
    menu->addStateToLastButton("2");
    menu->addStateToLastButton("3");
    menu->addStateToLastButton("4");
    menu->addStateToLastButton("5");
    menu->addStateToLastButton("10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewButton("play", &IMenuManager::launchNewGame,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setNewGameMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeIASelection3Menu()
  {
    Menu* menu = new Menu("iaselection3", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("lvl ia 3", NULL, 3,
    			       glm::vec4(1, 1, 0, 1), "easy");
    menu->addStateToLastButton("medium");
    menu->addStateToLastButton("hard");
    menu->createNewStateButton("nb ia", NULL, 6,
			       glm::vec4(1, 1, 0, 1), "0");
    menu->addStateToLastButton("1");
    menu->addStateToLastButton("2");
    menu->addStateToLastButton("3");
    menu->addStateToLastButton("4");
    menu->addStateToLastButton("5");
    menu->addStateToLastButton("10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewButton("team 4", &IMenuManager::setIASelection4Menu,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setNewGameMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeIASelection4Menu();
    return (true);
  }

  bool		MenuState::_initializeIASelection2Menu()
  {
    Menu* menu = new Menu("iaselection2", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("lvl ia 2", NULL, 3,
    			       glm::vec4(0, 1, 1, 1), "easy");
    menu->addStateToLastButton("medium");
    menu->addStateToLastButton("hard");
    menu->createNewStateButton("nb ia", NULL, 6,
			       glm::vec4(0, 1, 1, 1), "0");
    menu->addStateToLastButton("1");
    menu->addStateToLastButton("2");
    menu->addStateToLastButton("3");
    menu->addStateToLastButton("4");
    menu->addStateToLastButton("5");
    menu->addStateToLastButton("10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewButton("team 3", &IMenuManager::setIASelection3Menu,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setNewGameMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeIASelection3Menu();
    return (true);
  }

  bool		MenuState::_initializeIASelection1Menu()
  {
    Menu* menu = new Menu("iaselection1", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("lvl ia 1", NULL, 3,
			       glm::vec4(0, 0, 1, 1), "easy");
    menu->addStateToLastButton("medium");
    menu->addStateToLastButton("hard");
    menu->createNewStateButton("nb ia", NULL, 6,
			       glm::vec4(0, 0, 1, 1), "0");
    menu->addStateToLastButton("1");
    menu->addStateToLastButton("2");
    menu->addStateToLastButton("3");
    menu->addStateToLastButton("4");
    menu->addStateToLastButton("5");
    menu->addStateToLastButton("10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewButton("team 2", &IMenuManager::setIASelection2Menu,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setNewGameMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeIASelection2Menu();
    return (true);
  }

  bool		MenuState::_initializePlayerSelectionMenu()
  {
    Menu* menu = new Menu("playerselection", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("player 1", NULL, 3,
			       glm::vec4(0, 0, 1, 1), "ok");
    menu->createNewStateButton("player 2", NULL, 3, glm::vec4(0, 1, 1, 1), "x");
    menu->addStateToLastButton("ok");
    menu->createNewStateButton("player 3", NULL, 3, glm::vec4(1, 0, 1, 1), "x");
    menu->addStateToLastButton("ok");
    menu->createNewStateButton("player 4", NULL, 3, glm::vec4(1, 1, 0, 1), "x");
    menu->addStateToLastButton("ok");
    menu->createNewButton("next",&IMenuManager::setIASelection1Menu,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setMainMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_initializeIASelection1Menu();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeMapParamsMenu()
  {
    Menu* menu = new Menu("mapparams", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("map width", NULL, 4,
			       glm::vec4(1, 1, 1, 1), "10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewStateButton("map height", NULL, 3,
			       glm::vec4(1, 1, 1, 1), "10");
    menu->addStateToLastButton("15");
    menu->addStateToLastButton("20");
    menu->addStateToLastButton("25");
    menu->addStateToLastButton("50");
    menu->addStateToLastButton("100");
    menu->createNewButton("next", &IMenuManager::setNewGameMenu,
			  glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setPlayMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializePlayMenu()
  {
    Menu* menu = new Menu("play", this);
    if (!menu->initialize())
      return (false);
    menu->createNewButton("new", &IMenuManager::setMapParamsMenu,
  			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("continue", &IMenuManager::setContinueGameMenu,
  			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("load", &IMenuManager::setLoadGameMenu,
  			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("back", &IMenuManager::setMainMenu,
  			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeMapParamsMenu();
    this->_initializePlayerSelectionMenu();
    this->_initializeLoadGameMenu();
    return (true);
  }

  void		MenuState::_setBindingControlPlayer1(Menu* menu,
						     const std::string& first)
  {
    static std::list<std::string> list;
    if (list.size() == 0)
      {
	list.push_back("up");
	list.push_back("down");
	list.push_back("left");
	list.push_back("right");
	list.push_back("0");
	list.push_back("1");
	list.push_back("rshift");
	list.push_back("rctrl");
	list.push_back("enter");
      }
    for (std::list<std::string>::iterator it = list.begin();
    	 it != list.end(); it++)
      {
    	if ((*it) != first)
    	  menu->addStateToLastButton(*it);
      }
  }

  void		MenuState::_setBindingControlPlayer2(Menu* menu,
						     const std::string& first)
  {
    static std::list<std::string> list;
    if (list.size() == 0)
      {
	list.push_back("a");
	list.push_back("z");
	list.push_back("e");
	list.push_back("r");
	list.push_back("q");
	list.push_back("s");
	list.push_back("d");
	list.push_back("f");
	list.push_back("w");
	list.push_back("x");
	list.push_back("c");
	list.push_back("v");
      }
    for (std::list<std::string>::iterator it = list.begin();
	 it != list.end(); it++)
      {
	if ((*it) != first)
	  menu->addStateToLastButton(*it);
      }
  }

  bool		MenuState::_initializeControlPlayer1()
  {
    Menu* menu = new Menu("controlplayer1", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("up", NULL, 7,
			       glm::vec4(1, 1, 1, 1), "up");
    this->_setBindingControlPlayer1(menu, "up");
    menu->createNewStateButton("down", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "down");
    this->_setBindingControlPlayer1(menu, "down");
    menu->createNewStateButton("left", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "left");
    this->_setBindingControlPlayer1(menu, "left");
    menu->createNewStateButton("right", NULL, 4,
			       glm::vec4(1, 1, 1, 1), "right");
    this->_setBindingControlPlayer1(menu, "right");
    menu->createNewStateButton("drop", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "0");
    this->_setBindingControlPlayer1(menu, "0");
    menu->createNewStateButton("special", NULL, 2,
			       glm::vec4(1, 1, 1, 1), "1");
    this->_setBindingControlPlayer1(menu, "1");
    menu->createNewButton("ok", NULL, glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeControlPlayer2()
  {
    Menu* menu = new Menu("controlplayer2", this);
    if (!menu->initialize())
      return (false);
    menu->createNewStateButton("up", NULL, 7,
			       glm::vec4(1, 1, 1, 1), "z");
    this->_setBindingControlPlayer2(menu, "z");
    menu->createNewStateButton("down", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "s");
    this->_setBindingControlPlayer2(menu, "s");
    menu->createNewStateButton("left", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "q");
    this->_setBindingControlPlayer2(menu, "q");
    menu->createNewStateButton("right", NULL, 4,
			       glm::vec4(1, 1, 1, 1), "d");
    this->_setBindingControlPlayer2(menu, "d");
    menu->createNewStateButton("drop", NULL, 5,
			       glm::vec4(1, 1, 1, 1), "x");
    this->_setBindingControlPlayer2(menu, "x");
    menu->createNewStateButton("special", NULL, 2,
			       glm::vec4(1, 1, 1, 1), "w");
    this->_setBindingControlPlayer2(menu, "w");
    menu->createNewButton("ok", NULL, glm::vec4(0, 1, 0, 1));
    menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			  glm::vec4(1, 0, 0, 1));
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeOptionControlMenu()
  {
    Menu* menu = new Menu("control", this);
    if (!menu->initialize())
      return (false);

    menu->createNewButton("p1", &IMenuManager::setOptionControlPlayer1,
			  glm::vec4(0, 0, 1, 1));
    menu->createNewButton("p2", &IMenuManager::setOptionControlPlayer2,
			  glm::vec4(0, 1, 1, 1));
    menu->createNewButton("ok", &IMenuManager::setOptionsMenu,
    			  glm::vec4(0, 1, 0, 1), true);
    menu->createNewButton("cancel", &IMenuManager::setOptionsMenu,
    			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeControlPlayer1();
    this->_initializeControlPlayer2();
    return (true);
  }

  bool		MenuState::_initializeOptionAudioMenu()
  {
    Menu* menu = new Menu("audio", this);
    if (!menu->initialize())
      return (false);
    menu->createNewToggleButton("sound", &IMenuManager::setMainMenu);
    menu->createNewToggleButton("music", &IMenuManager::setMainMenu);
    menu->createNewButton("ok", &IMenuManager::setOptionsMenu,
			  glm::vec4(0, 1, 0, 1), true);
    menu->createNewButton("cancel", &IMenuManager::setOptionsMenu,
			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeOptionsMenu()
  {
    Menu* menu = new Menu("options", this);
    if (!menu->initialize())
      return (false);
    menu->createNewButton("audio", &IMenuManager::setOptionsAudioMenu,
			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("control", &IMenuManager::setOptionsControlMenu,
			  glm::vec4(1, 1, 1, 1), true);
    menu->createNewButton("back", &IMenuManager::setMainMenu,
			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_initializeOptionControlMenu();
    this->_initializeOptionAudioMenu();
    return (true);
  }

  bool		MenuState::_initializeHighscoresMenu()
  {
    Menu* menu = new Menu("highscores", this);
    if (!menu->initialize())
      return (false);
    menu->createNewButton("back", &IMenuManager::setMainMenu,
			  glm::vec4(1, 0, 0, 1), true);
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  void		MenuState::_setNewCurrentMenu(const std::string& name)
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

  void		MenuState::initialize()
  {
    if (!this->_skybox.initialize())
      std::cerr << "Error initializing skybox" << std::endl;
    if (!this->_initializeMainMenu())
      std::cerr << "Error initializing main menu" << std::endl;
    if (!this->_initializePlayMenu())
      std::cerr << "Error initializing play menu" << std::endl;
    if (!this->_initializeOptionsMenu())
      std::cerr << "Error initializing options menu" << std::endl;
    if (!this->_initializeHighscoresMenu())
      std::cerr << "Error initializing high score menu" << std::endl;
  }

  void		MenuState::release()
  {
  }

  void		MenuState::obscuring()
  {
  }

  void		MenuState::update(float, const Input& input)
  {
    glDisable(GL_CULL_FACE);
    this->_currentMenu->update(input);
    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	this->_manager.pop();
	return ;
      }
    this->_skybox.update();
  }

  void		MenuState::draw(float, Screen& context)
  {
    Transform	perspective = ProjectionPerspective(60, 1024/768, 1.0f, 1000);
    Transform	camera = Camera(glm::vec3(10, 0, 0),
				glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    RenderState state(perspective, camera);

    context.split(glm::ivec2(0, 0), glm::ivec2(1024 * 1.5, 768 * 1.5));
    context.clear();
    context.draw(this->_skybox, state);
    context.draw(*this->_currentMenu, state);
    context.flush();
  }

  void		MenuState::revealing()
  {
    this->_setNewCurrentMenu("bomberman");
  }

  void		MenuState::setOptionControlPlayer1()
  {
    this->_setNewCurrentMenu("controlplayer1");
  }

  void		MenuState::setOptionControlPlayer2()
  {
    this->_setNewCurrentMenu("controlplayer2");
  }

  void		MenuState::setNextFrame()
  {
    this->_currentMenu->setNextFrame();
  }

  void		MenuState::setPrevFrame()
  {
    this->_currentMenu->setPrevFrame();
  }

  void		MenuState::setPlayMenu()
  {
    this->_setNewCurrentMenu("play");
  }

  void		MenuState::setOptionsMenu()
  {
    this->_setNewCurrentMenu("options");
  }

  void		MenuState::setHighScoreMenu()
  {
    this->_setNewCurrentMenu("highscores");
  }

  void		MenuState::exitGame()
  {
    this->_manager.pop();
  }

  void		MenuState::launchNewGame()
  {
<<<<<<< HEAD
    IGameState*	state = new GameState(this->_manager);
    //this->_manager.pop();
=======
    GameState*	state = new GameState(this->_manager);
    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->deserializeFromFile("save1.json", *state);
	// s->serializeToFile("export1.json", *state);
      }
    catch (SerializerException& ex)
      {
	std::cout << "Serializer GameState Error : " << ex.what() << std::endl;
      }
    this->_manager.pop();
>>>>>>> 526a398256b21cf30d6e79b1ed64c2e894375da9
    this->_manager.push(state);
  }

  void		MenuState::setMapParamsMenu()
  {
    this->_setNewCurrentMenu("mapparams");
  }

  void		MenuState::setNewGameMenu()
  {
    this->_setNewCurrentMenu("playerselection");
  }

  void		MenuState::setIASelection1Menu()
  {
    this->_setNewCurrentMenu("iaselection1");
  }

  void		MenuState::setIASelection2Menu()
  {
    this->_setNewCurrentMenu("iaselection2");
  }

  void		MenuState::setIASelection3Menu()
  {
    this->_setNewCurrentMenu("iaselection3");
  }

  void		MenuState::setIASelection4Menu()
  {
    this->_setNewCurrentMenu("iaselection4");
  }

  void		MenuState::setContinueGameMenu()
  {
  }

  void		MenuState::setLoadGameMenu()
  {
    this->_setNewCurrentMenu("loadcampaign");
  }

  void		MenuState::setMainMenu()
  {
    this->_setNewCurrentMenu("bomberman");
  }

  void		MenuState::setOptionsAudioMenu()
  {
    this->_setNewCurrentMenu("audio");
  }

  void		MenuState::setOptionsControlMenu()
  {
    this->_setNewCurrentMenu("control");
  }

  MenuState::~MenuState()
  {
    for (std::list<Menu*>::iterator it = this->_menuList.begin();
	 it != this->_menuList.end(); it++)
      delete (*it);
  }
}
