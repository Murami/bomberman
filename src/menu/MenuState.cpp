#include		<stdexcept>
#include		"FileExplorer.hh"
#include		"events/Input.hh"
#include		"game/GameManager.hh"
#include		"game/GameLoadingState.hh"
#include		"graphic/Screen.hh"
#include		"graphic/Camera.hh"
#include		"graphic/ProjectionPerspective.hh"
#include		"MenuState.hh"
#include		"PauseState.hh"
#include		"serializer/ISerializedNode.hh"
#include		"serializer/JSONSerializer.hh"
#include		"serializer/Serializer.hh"
#include		"serializer/SerializerException.hh"
#include		"sound/SoundManager.hh"

namespace	bbm
{
  const std::string	MenuState::INPUT_CONFIG_P1 = "./input/inputConfig1.json";
  const std::string	MenuState::INPUT_CONFIG_P2 = "./input/inputConfig2.json";
  const std::string	MenuState::INPUT_CONFIG_P3 = "./input/inputConfig3.json";
  const std::string	MenuState::INPUT_CONFIG_P4 = "./input/inputConfig4.json";

  MenuState::MenuState(GameManager& manager) : _manager(manager)
  {
    SoundManager::getInstance()->addMusic("menu", "assets/sound/heart_of_courage.mp3");
    SoundManager::getInstance()->addMusic("wait", "assets/sound/wait.mp3");
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    SDL_ShowCursor(SDL_DISABLE);
  }

  bool		MenuState::_initializeMainMenu()
  {
    Menu* menu = new Menu("bomberman", this);
    menu->initialize();
    try
      {
	menu->createNewButton("play", &IMenuManager::setPlayMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("options", &IMenuManager::setOptionsMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("highscores", &IMenuManager::setHighScoreMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("quit", &IMenuManager::exitGame,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << std::endl;
	return (false);
      }
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
    try
      {
	menu->createNewButton("next", &IMenuManager::setNextFrame,
			      glm::vec4(1, 1, 1, 1), false);
	menu->createNewButton("prev", &IMenuManager::setPrevFrame,
			      glm::vec4(1, 1, 1, 1), false);
	menu->createNewButton("play", &IMenuManager::launchLoadedGame,
			      glm::vec4(0, 1, 0, 1), false);
	menu->createNewButton("back", &IMenuManager::setPlayMenu,
			      glm::vec4(1, 0, 0, 1), true);
	menu->createFrame();
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeIASelectionMenu()
  {
    Menu* menu = new Menu("iaselection", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewStateButton("number", NULL, 9,
				   glm::vec4(1, 1, 1, 1), "0");
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
	menu->createNewStateButton("enemies level", NULL, 2,
				   glm::vec4(1, 1, 1, 1), "easy");
	menu->addStateToLastButton("medium");
	menu->addStateToLastButton("hard");
	menu->createNewButton("play", &IMenuManager::launchNewGame,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setNewGameMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }


  bool		MenuState::_initializePlayerSelectionMenu()
  {
    Menu* menu = new Menu("playerselection", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewStateButton("player 1", NULL, 3,
				   glm::vec4(0, 0, 1, 1), "gamepad 1");
	menu->addStateToLastButton("gamepad 2");
	menu->addStateToLastButton("gamepad 3");
	menu->addStateToLastButton("gamepad 4");
	menu->createNewStateButton("player 2", NULL, 3,
				   glm::vec4(0, 1, 1, 1), "x");
	menu->addStateToLastButton("gamepad 1");
	menu->addStateToLastButton("gamepad 2");
	menu->addStateToLastButton("gamepad 3");
	menu->addStateToLastButton("gamepad 4");
	menu->createNewStateButton("player 3", NULL, 3,
				   glm::vec4(1, 0, 1, 1), "x");
	menu->addStateToLastButton("gamepad 1");
	menu->addStateToLastButton("gamepad 2");
	menu->addStateToLastButton("gamepad 3");
	menu->addStateToLastButton("gamepad 4");
	menu->createNewStateButton("player 4", NULL, 3,
				   glm::vec4(1, 1, 0, 1), "x");
	menu->addStateToLastButton("gamepad 1");
	menu->addStateToLastButton("gamepad 2");
	menu->addStateToLastButton("gamepad 3");
	menu->addStateToLastButton("gamepad 4");
	menu->createNewButton("next",&IMenuManager::setIASelectionMenu,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setMainMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (this->_initializeIASelectionMenu());
  }

  bool		MenuState::_initializeMapParamsMenu()
  {
    Menu* menu = new Menu("mapparams", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewStateButton("map width", NULL, 4,
				   glm::vec4(1, 1, 1, 1), "20");
	menu->addStateToLastButton("50");
	menu->addStateToLastButton("75");
	menu->addStateToLastButton("100");
	menu->addStateToLastButton("150");
	menu->addStateToLastButton("200");
	menu->createNewStateButton("map height", NULL, 3,
				   glm::vec4(1, 1, 1, 1), "20");
	menu->addStateToLastButton("50");
	menu->addStateToLastButton("75");
	menu->addStateToLastButton("100");
	menu->addStateToLastButton("150");
	menu->addStateToLastButton("200");
	menu->createNewButton("next", &IMenuManager::setNewGameMenu,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setPlayMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializePlayMenu()
  {
    Menu* menu = new Menu("play", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("new", &IMenuManager::setMapParamsMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("load", &IMenuManager::setLoadGameMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("back", &IMenuManager::setMainMenu,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    if (!this->_initializeMapParamsMenu() ||
	!this->_initializePlayerSelectionMenu() ||
	!this->_initializeLoadGameMenu())
      return (false);
    return (true);
  }

  void		MenuState::_setBindingControlPlayer1(Menu* menu,
						     const std::string& first)
  {
    if (this->_SDLInputsList.size() == 0)
      {
	this->_SDLInputsList.push_back("BACKSPACE");
	this->_SDLInputsList.push_back("PAUSE");
	this->_SDLInputsList.push_back("SPACE");
	this->_SDLInputsList.push_back("QUOTEDBL");
	this->_SDLInputsList.push_back("HASH");
	this->_SDLInputsList.push_back("DOLLAR");
	this->_SDLInputsList.push_back("AMPERSAND");
	this->_SDLInputsList.push_back("QUOTE");
	this->_SDLInputsList.push_back("LEFTPAREN");
	this->_SDLInputsList.push_back("RIGHTPAREN");
	this->_SDLInputsList.push_back("ASTERISK");
	this->_SDLInputsList.push_back("PLUS");
	this->_SDLInputsList.push_back("COMMA");
	this->_SDLInputsList.push_back("MINUS");
	this->_SDLInputsList.push_back("PERIOD");
	this->_SDLInputsList.push_back("SLASH");
	this->_SDLInputsList.push_back("0");
	this->_SDLInputsList.push_back("1");
	this->_SDLInputsList.push_back("2");
	this->_SDLInputsList.push_back("3");
	this->_SDLInputsList.push_back("4");
	this->_SDLInputsList.push_back("5");
	this->_SDLInputsList.push_back("6");
	this->_SDLInputsList.push_back("7");
	this->_SDLInputsList.push_back("8");
	this->_SDLInputsList.push_back("9");
	this->_SDLInputsList.push_back("COLON");
	this->_SDLInputsList.push_back("SEMICOLON");
	this->_SDLInputsList.push_back("LESS");
	this->_SDLInputsList.push_back("EQUALS");
	this->_SDLInputsList.push_back("GREATER");
	this->_SDLInputsList.push_back("QUESTION");
	this->_SDLInputsList.push_back("AT");
	this->_SDLInputsList.push_back("LEFTBRACKET");
	this->_SDLInputsList.push_back("BACKSLASH");
	this->_SDLInputsList.push_back("RIGHTBRACKET");
	this->_SDLInputsList.push_back("CARET");
	this->_SDLInputsList.push_back("UNDERSCORE");
	this->_SDLInputsList.push_back("BACKQUOTE");
	this->_SDLInputsList.push_back("a");
	this->_SDLInputsList.push_back("b");
	this->_SDLInputsList.push_back("c");
	this->_SDLInputsList.push_back("d");
	this->_SDLInputsList.push_back("e");
	this->_SDLInputsList.push_back("f");
	this->_SDLInputsList.push_back("g");
	this->_SDLInputsList.push_back("h");
	this->_SDLInputsList.push_back("i");
	this->_SDLInputsList.push_back("j");
	this->_SDLInputsList.push_back("k");
	this->_SDLInputsList.push_back("l");
	this->_SDLInputsList.push_back("m");
	this->_SDLInputsList.push_back("n");
	this->_SDLInputsList.push_back("o");
	this->_SDLInputsList.push_back("p");
	this->_SDLInputsList.push_back("q");
	this->_SDLInputsList.push_back("r");
	this->_SDLInputsList.push_back("s");
	this->_SDLInputsList.push_back("t");
	this->_SDLInputsList.push_back("u");
	this->_SDLInputsList.push_back("v");
	this->_SDLInputsList.push_back("w");
	this->_SDLInputsList.push_back("x");
	this->_SDLInputsList.push_back("y");
	this->_SDLInputsList.push_back("z");
	this->_SDLInputsList.push_back("DELETE");
	this->_SDLInputsList.push_back("KP_0");
	this->_SDLInputsList.push_back("KP_1");
	this->_SDLInputsList.push_back("KP_2");
	this->_SDLInputsList.push_back("KP_3");
	this->_SDLInputsList.push_back("KP_4");
	this->_SDLInputsList.push_back("KP_5");
	this->_SDLInputsList.push_back("KP_6");
	this->_SDLInputsList.push_back("KP_7");
	this->_SDLInputsList.push_back("KP_8");
	this->_SDLInputsList.push_back("KP_9");
	this->_SDLInputsList.push_back("KP_DIVIDE");
	this->_SDLInputsList.push_back("KP_MULTIPLY");
	this->_SDLInputsList.push_back("KP_MINUS");
	this->_SDLInputsList.push_back("KP_PLUS");
	this->_SDLInputsList.push_back("UP");
	this->_SDLInputsList.push_back("DOWN");
	this->_SDLInputsList.push_back("RIGHT");
	this->_SDLInputsList.push_back("LEFT");
	this->_SDLInputsList.push_back("CAPSLOCK");
	this->_SDLInputsList.push_back("RSHIFT");
	this->_SDLInputsList.push_back("LSHIFT");
	this->_SDLInputsList.push_back("RCTRL");
	this->_SDLInputsList.push_back("LCTRL");
	this->_SDLInputsList.push_back("RALT");
	this->_SDLInputsList.push_back("LALT");
      }
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
    	 it != this->_SDLInputsList.end(); it++)
      {
    	if ((*it) != first)
    	  menu->addStateToLastButton(*it);
      }
  }

  void		MenuState::_setBindingControlPlayer2(Menu* menu,
						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
	 it != this->_SDLInputsList.end(); it++)
      {
	if ((*it) != first)
	  menu->addStateToLastButton(*it);
      }
  }

  void		MenuState::_setBindingControlPlayer3(Menu* menu,
						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
	 it != this->_SDLInputsList.end(); it++)
      {
	if ((*it) != first)
	  menu->addStateToLastButton(*it);
      }
  }

  void		MenuState::_setBindingControlPlayer4(Menu* menu,
						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
	 it != this->_SDLInputsList.end(); it++)
      {
	if ((*it) != first)
	  menu->addStateToLastButton(*it);
      }
  }

  const std::string&	MenuState::_getKeyFromSDLK(const std::string& key)
  {
    static std::string newKey;
    size_t pos = key.rfind("_");
    if (pos != std::string::npos)
      {
	newKey = std::string(&key[pos+1]);
	return (newKey);
      }
    return (key);
  }

  bool		MenuState::_initializeControlPlayer1()
  {
    Menu* menu = new Menu("controlplayer1", this);
    if (!menu->initialize())
      {
	std::cerr << "Error initializing menu" << std::endl;
	return (false);
      }
    try
      {
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("up")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("down")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("left")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("right")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb2")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer1,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (this->_initializeControlPlayer2());
  }

  bool		MenuState::_initializeControlPlayer2()
  {
    Menu* menu = new Menu("controlplayer2", this);
    if (!menu->initialize())
      {
	std::cerr << "Error initializing menu" << std::endl;
	return (false);
      }
    try
      {
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("up")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("down")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("left")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("right")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb2")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer4,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (this->_initializeControlPlayer3());
  }

  bool		MenuState::_initializeControlPlayer3()
  {
    Menu* menu = new Menu("controlplayer3", this);
    if (!menu->initialize())
      {
	std::cerr << "Error initializing menu" << std::endl;
	return (false);
      }
    try
      {
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("up")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("down")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("left")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("right")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb2")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer4,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    std::cout << "pushing menu control player 3" << std::endl;
    this->_menuList.push_back(menu);
    return (this->_initializeControlPlayer4());
  }

  bool		MenuState::_initializeControlPlayer4()
  {
    Menu* menu = new Menu("controlplayer4", this);
    if (!menu->initialize())
      {
	std::cerr << "Error initializing menu" << std::endl;
	return (false);
      }
    try
      {
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("up")));
	this->_setBindingControlPlayer4(menu,
					this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("up")));
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("down")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("left")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("right")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb2")));
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer4,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("cancel", &IMenuManager::setOptionsControlMenu,
			      glm::vec4(1, 0, 0, 1));
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeOptionControlMenu()
  {
    Menu* menu = new Menu("control", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("player 1",
			      &IMenuManager::setOptionControlPlayer1,
			      glm::vec4(0, 0, 1, 1));
	menu->createNewButton("player 2",
			      &IMenuManager::setOptionControlPlayer2,
			      glm::vec4(0, 1, 1, 1));
	menu->createNewButton("player 3",
			      &IMenuManager::setOptionControlPlayer3,
			      glm::vec4(1, 0, 1, 1));
	menu->createNewButton("player 4",
			      &IMenuManager::setOptionControlPlayer4,
			      glm::vec4(1, 1, 0, 1));
	menu->createNewButton("back", &IMenuManager::setOptionsMenu,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    if (!this->_initializeControlPlayer1())
      return (false);
    return (true);
  }

  bool		MenuState::_initializeOptionAudioMenu()
  {
    Menu* menu = new Menu("audio", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewToggleButton("sound", NULL);
	menu->createNewToggleButton("music", NULL);
	menu->createNewButton("ok", &IMenuManager::serializeAudioSettings,
			      glm::vec4(0, 1, 0, 1), true);
	menu->createNewButton("cancel", &IMenuManager::setOptionsMenu,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeOptionsMenu()
  {
    Menu* menu = new Menu("options", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("audio", &IMenuManager::setOptionsAudioMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("control", &IMenuManager::setOptionsControlMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("back", &IMenuManager::setMainMenu,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
	return (false);
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    if (!this->_initializeOptionControlMenu())
      return (false);
    return (this->_initializeOptionAudioMenu());
  }

  bool		MenuState::_initializeHighscoresMenu()
  {
    Menu* menu = new Menu("highscores", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("back", &IMenuManager::setMainMenu,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << ": Not found" << std::endl;
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    return (true);
  }

  bool		MenuState::_initializeInputConfig()
  {
    this->_inputConfigPlayer1 = new InputConfig();
    this->_inputConfigPlayer1->load(INPUT_CONFIG_P1);
    this->_inputConfigPlayer2 = new InputConfig();
    this->_inputConfigPlayer2->load(INPUT_CONFIG_P2);
    this->_inputConfigPlayer3 = new InputConfig();
    this->_inputConfigPlayer3->load(INPUT_CONFIG_P3);
    this->_inputConfigPlayer4 = new InputConfig();
    this->_inputConfigPlayer4->load(INPUT_CONFIG_P4);
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
    throw (std::runtime_error(std::string("Error initializing ") + name));
    std::cerr << "Setting new menu : \'" << name << "\' : not found"
	      << std::endl;
  }

  void		MenuState::initialize()
  {
    memset(&this->_config, 0, sizeof(this->_config));
    this->_initializeInputConfig();
    SoundManager::getInstance()->stop("theme");
    try
      {
	this->_skybox.initialize();
      }
    catch (FileLoadingException e)
      {
	std::cerr << "Error initializing Skybox : " << e.what() << std::endl;
      }
    if (!this->_initializeMainMenu())
      std::cerr << "Error initializing main menu" << std::endl;
    if (!this->_initializePlayMenu())
      std::cerr << "Error initializing play menu" << std::endl;
    if (!this->_initializeOptionsMenu())
      std::cerr << "Error initializing options menu" << std::endl;
    if (!this->_initializeHighscoresMenu())
      std::cerr << "Error initializing high score menu" << std::endl;
  }

  void		MenuState::release() {}
  void		MenuState::obscuring() {}

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
    Transform	perspective = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 0.1f, 1000);
    Transform	camera = Camera(glm::vec3(10, 0, 0),
				glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    RenderState state(perspective, camera);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();
    context.draw(this->_skybox, state);
    context.draw(*this->_currentMenu, state);
    context.flush();
  }

  void		MenuState::revealing()
  {
    this->_setNewCurrentMenu("bomberman");
  }

  void		MenuState::serializeAudioSettings(Menu *menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    int i = 0;
    while (it != list.end())
      {
	ToggleButton* s = dynamic_cast<ToggleButton*>(*it);
	if (s)
	  {
	    if (i == 0)
	      {
		this->_config.sound = s->isChecked();
	      }
	    else
	      {
		this->_config.music = s->isChecked();
		if (this->_config.music)
		  SoundManager::getInstance()->playMusic("menu");
		else
		  SoundManager::getInstance()->stop("menu");
	      }
	    i++;
	  }
      	it++;
      }
    this->setOptionsMenu(menu);
  }

  void		MenuState::serializeBindingPlayer1(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    while (it != list.end())
      {
	StateButton* s = dynamic_cast<StateButton*>(*it);
	if (s)
	  {
	    if (s->getState()[0] >= '0' && s->getState()[0] <= '9')
	      {
	    	std::string key("SDLK_KP_");
	    	key += s->getState();
	    	this->_inputConfigPlayer1->bindKey(s->getLabel(), key);
	      }
	    else
	      {
	    	std::string key("SDLK_");
	    	key += s->getState();
	    	this->_inputConfigPlayer1->bindKey(s->getLabel(), key);
	      }
	  }
      	it++;
      }
    this->_inputConfigPlayer1->save(INPUT_CONFIG_P1);
    this->setOptionsControlMenu(menu);
  }

  void		MenuState::serializeBindingPlayer2(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    while (it != list.end())
      {
	StateButton* s = dynamic_cast<StateButton*>(*it);
	if (s)
	  {
	    if (s->getState()[0] >= '0' && s->getState()[0] <= '9')
	      {
	    	std::string key("SDLK_KP_");
	    	key += s->getState();
	    	this->_inputConfigPlayer2->bindKey(s->getLabel(), key);
	      }
	    else
	      {
	    	std::string key("SDLK_");
	    	key += s->getState();
	    	this->_inputConfigPlayer2->bindKey(s->getLabel(), key);
	      }
	  }
      	it++;
      }
    this->_inputConfigPlayer2->save(INPUT_CONFIG_P2);
    this->setOptionsControlMenu(menu);
  }

  void		MenuState::serializeBindingPlayer3(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    while (it != list.end())
      {
	StateButton* s = dynamic_cast<StateButton*>(*it);
	if (s)
	  {
	    if (s->getState()[0] >= '0' && s->getState()[0] <= '9')
	      {
	    	std::string key("SDLK_KP_");
	    	key += s->getState();
	    	this->_inputConfigPlayer3->bindKey(s->getLabel(), key);
	      }
	    else
	      {
	    	std::string key("SDLK_");
	    	key += s->getState();
	    	this->_inputConfigPlayer3->bindKey(s->getLabel(), key);
	      }
	  }
      	it++;
      }
    this->_inputConfigPlayer3->save(INPUT_CONFIG_P3);
    this->setOptionsControlMenu(menu);
  }

  void		MenuState::serializeBindingPlayer4(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    while (it != list.end())
      {
	StateButton* s = dynamic_cast<StateButton*>(*it);
	if (s)
	  {
	    if (s->getState()[0] >= '0' && s->getState()[0] <= '9')
	      {
	    	std::string key("SDLK_KP_");
	    	key += s->getState();
	    	this->_inputConfigPlayer4->bindKey(s->getLabel(), key);
	      }
	    else
	      {
	    	std::string key("SDLK_");
	    	key += s->getState();
	    	this->_inputConfigPlayer4->bindKey(s->getLabel(), key);
	      }
	  }
      	it++;
      }
    this->_inputConfigPlayer4->save(INPUT_CONFIG_P4);
    this->setOptionsControlMenu(menu);
  }

  void		MenuState::setOptionControlPlayer1(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer1");
  }

  void		MenuState::setOptionControlPlayer2(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer2");
  }

  void		MenuState::setOptionControlPlayer3(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer3");
  }

  void		MenuState::setOptionControlPlayer4(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer4");
  }

  void		MenuState::setNextFrame(Menu*)
  {
    this->_currentMenu->setNextFrame();
  }

  void		MenuState::setPrevFrame(Menu*)
  {
    this->_currentMenu->setPrevFrame();
  }

  void		MenuState::setPlayMenu(Menu*)
  {
    this->_setNewCurrentMenu("play");
  }

  void		MenuState::setOptionsMenu(Menu*)
  {
    this->_setNewCurrentMenu("options");
  }

  void		MenuState::setHighScoreMenu(Menu*)
  {
    this->_setNewCurrentMenu("highscores");
  }

  void		MenuState::exitGame(Menu*)
  {
    this->_manager.pop();
  }

  void		MenuState::launchLoadedGame(Menu* menu)
  {
    FileExplorer*	explorer = menu->getExplorer();
    std::string tmp = explorer->getCurrentFile();
    std::string tmp2;
    size_t pos = tmp.find(".save");

    this->_config.newGame = false;
    SoundManager::getInstance()->stop("menu");
    if (this->_config.music)
      SoundManager::getInstance()->playMusic("wait");
    for (size_t i = 0; i < pos; i++)
      tmp2 += tmp[i];
    this->_config.fileToLoad = new std::string(tmp2);
    GameLoadingState*	state = new GameLoadingState(this->_manager,
    						     &this->_config);
    this->_manager.push(state);
  }

  void		MenuState::launchNewGame(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    StateButton*	nbIAButton = dynamic_cast<StateButton*>(*it);

    SoundManager::getInstance()->stop("menu");
    if (this->_config.music)
      SoundManager::getInstance()->playMusic("wait");
    if (nbIAButton)
      {
	std::stringstream ss;
	ss << nbIAButton->getState();
	ss >> this->_config.numberIA;
      }
    it++;
    StateButton*	level = dynamic_cast<StateButton*>(*it);
    if (level)
      this->_config.level = level->getState();
    this->_config.newGame = true;
    GameLoadingState*	state = new GameLoadingState(this->_manager,
    						     &this->_config);
    this->_manager.push(state);
  }

  void		MenuState::setMapParamsMenu(Menu*)
  {
    this->_setNewCurrentMenu("mapparams");
  }

  void		MenuState::setNewGameMenu(Menu* menu)
  {
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    StateButton* s = dynamic_cast<StateButton*>(*it);
    std::stringstream ss;
    ss.clear();
    ss << s->getState();
    ss >> this->_config.mapSizeX;
    it++;
    StateButton* s2 = dynamic_cast<StateButton*>(*it);
    std::stringstream ss2;
    ss2.clear();
    ss2 << s2->getState();
    ss2.clear();
    ss2 >> this->_config.mapSizeY;
    std::cout << "Sending map size : x = " << this->_config.mapSizeX << " y = " << this->_config.mapSizeY << std::endl;
    this->_setNewCurrentMenu("playerselection");
  }

  void		MenuState::setIASelectionMenu(Menu* menu)
  {
    int		tab[4];
    this->_config.nbPlayers = 1;
    tab[0] = 1;
    tab[1] = tab[2] = tab[3] = 0;
    std::list<AButton*> list = menu->getButtons();
    std::list<AButton*>::iterator it = list.begin();
    int i = 0;
    while (it != list.end())
      {
	StateButton* s = dynamic_cast<StateButton*>(*it);
	if (s)
	  {
	    std::stringstream ss;
	    std::string state = s->getState();
	    for (char c = '1'; c < '5'; c++)
	      {
		std::string tmp;
		tmp += c;
		if (state.find(tmp) != std::string::npos)
		  {
		    if (i > 0)
		      this->_config.nbPlayers++;
		    tab[i] = c - 48;
		    break;
		  }
	      }
	  }
	i++;
	it++;
      }
    this->_config.player1 = tab[0];
    this->_config.player2 = tab[1];
    this->_config.player3 = tab[2];
    this->_config.player4 = tab[3];
    this->_setNewCurrentMenu("iaselection");
  }

  void		MenuState::setContinueGameMenu(Menu*) {}

  void		MenuState::setLoadGameMenu(Menu*)
  {
    this->_setNewCurrentMenu("loadcampaign");
    this->_currentMenu->refresh();
  }

  void		MenuState::setMainMenu(Menu*)
  {
    this->_setNewCurrentMenu("bomberman");
  }

  void		MenuState::setOptionsAudioMenu(Menu*)
  {
    this->_setNewCurrentMenu("audio");
  }

  void		MenuState::setOptionsControlMenu(Menu*)
  {
    this->_setNewCurrentMenu("control");
  }

  void		MenuState::resumeGame(Menu*) {}
  void		MenuState::saveGame(Menu*) {}

  MenuState::~MenuState()
  {
    SoundManager::getInstance()->stop("menu");
    for (std::list<Menu*>::iterator it = this->_menuList.begin();
    	 it != this->_menuList.end(); it++)
      delete (*it);
    if (this->_inputConfigPlayer1)
      delete (this->_inputConfigPlayer1);
    if (this->_inputConfigPlayer2)
      delete (this->_inputConfigPlayer2);
    if (this->_inputConfigPlayer3)
      delete (this->_inputConfigPlayer3);
    if (this->_inputConfigPlayer4)
      delete (this->_inputConfigPlayer4);
  }
}
