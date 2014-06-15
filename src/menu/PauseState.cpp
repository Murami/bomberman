//
// PauseState.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:48:02 2014 Manu
// Last update Sun Jun 15 12:16:32 2014 Manu
//

#include		<ctime>
#include		"menu/PauseState.hh"
#include		"game/GameManager.hh"
#include		"events/InputConfig.hh"
#include		"graphic/Screen.hh"
#include		"sound/SoundManager.hh"

namespace		bbm
{
  const std::string	PauseState::INPUT_CONFIG_P1 = "./input/inputConfig1.json";
  const std::string	PauseState::INPUT_CONFIG_P2 = "./input/inputConfig2.json";
  const std::string	PauseState::INPUT_CONFIG_P3 = "./input/inputConfig3.json";
  const std::string	PauseState::INPUT_CONFIG_P4 = "./input/inputConfig4.json";

  PauseState::PauseState(GameManager& manager, GameState& gameState,
			 GameLoadingState::GameConfig* gameConfig) :
    _manager(manager), _gameState(gameState), _config(gameConfig)
  {
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
  }

  const std::string&	PauseState::_getKeyFromSDLK(const std::string& key)
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
	menu->createNewButton("options", &IMenuManager::setOptionsMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("save and quit", &IMenuManager::saveGame,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("back to main menu", &IMenuManager::exitGame,
			      glm::vec4(1, 0, 0, 1), true);
      }
    catch (FileLoadingException e)
      {
	std::cerr << "In function " << __FUNCTION__ << " : "
		  << e.what() << std::endl;
      }
    menu->finalize();
    this->_menuList.push_back(menu);
    this->_currentMenu = menu;
    return (true);
  }

  bool		PauseState::_initializeOptionControlMenu()
  {
    Menu* menu = new Menu("control", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewButton("player 1",
			      &IMenuManager::setOptionControlPlayer1,
			      glm::vec4(1, 0, 0, 1));
	menu->createNewButton("player 2",
			      &IMenuManager::setOptionControlPlayer2,
			      glm::vec4(0, 1, 0, 1));
	menu->createNewButton("player 3",
			      &IMenuManager::setOptionControlPlayer3,
			      glm::vec4(0, 0, 1, 1));
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
    if (!this->_initializeControlPlayer())
      return (false);
    return (true);
  }

  bool		PauseState::_initializeControlPlayer()
  {
    Menu* menu = new Menu("controlplayer1", this);
    if (!menu->initialize())
      {
	std::cerr << "Error initializing menu" << std::endl;
	return (false);
      }
    try
      {
	std::string upKey = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("up"));
	std::string downKey = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("down"));
	std::string leftKey = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("left"));
	std::string rightKey = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("right"));
	std::string bombKey = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb"));
	std::string bomb2Key = this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb2"));
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1), upKey);
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1), downKey);
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1), leftKey);
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1), rightKey);
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1), bombKey);
	this->_setBindingControlPlayer1(menu, "");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1), bomb2Key);
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

  bool		PauseState::_initializeControlPlayer2()
  {
    Menu* menu = new Menu("controlplayer2", this);
    if (!menu->initialize())
      {
  	std::cerr << "Error initializing menu" << std::endl;
  	return (false);
      }
    try
      {
  	std::string upKey = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("up"));
  	std::string downKey = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("down"));
  	std::string leftKey = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("left"));
  	std::string rightKey = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("right"));
  	std::string bombKey = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb"));
  	std::string bomb2Key = this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb2"));
  	menu->createNewStateButton("up", NULL, 7,
  				   glm::vec4(1, 1, 1, 1), upKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("down", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), downKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("left", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), leftKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("right", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), rightKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), bombKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb2", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), bomb2Key);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer2,
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

  bool		PauseState::_initializeControlPlayer3()
  {
    Menu* menu = new Menu("controlplayer3", this);
    if (!menu->initialize())
      {
  	std::cerr << "Error initializing menu" << std::endl;
  	return (false);
      }
    try
      {
  	std::string upKey = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("up"));
  	std::string downKey = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("down"));
  	std::string leftKey = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("left"));
  	std::string rightKey = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("right"));
  	std::string bombKey = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb"));
  	std::string bomb2Key = this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb2"));
  	menu->createNewStateButton("up", NULL, 7,
  				   glm::vec4(1, 1, 1, 1), upKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("down", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), downKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("left", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), leftKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("right", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), rightKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), bombKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb2", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), bomb2Key);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewButton("ok", &IMenuManager::serializeBindingPlayer3,
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
    return (this->_initializeControlPlayer4());
  }

  bool		PauseState::_initializeControlPlayer4()
  {
    Menu* menu = new Menu("controlplayer4", this);
    if (!menu->initialize())
      {
  	std::cerr << "Error initializing menu" << std::endl;
  	return (false);
      }
    try
      {
  	std::string upKey = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("up"));
  	std::string downKey = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("down"));
  	std::string leftKey = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("left"));
  	std::string rightKey = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("right"));
  	std::string bombKey = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb"));
  	std::string bomb2Key = this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb2"));
  	menu->createNewStateButton("up", NULL, 7,
  				   glm::vec4(1, 1, 1, 1), upKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("down", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), downKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("left", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), leftKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("right", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), rightKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb", NULL, 5,
  				   glm::vec4(1, 1, 1, 1), bombKey);
  	this->_setBindingControlPlayer1(menu, "");
  	menu->createNewStateButton("bomb2", NULL, 4,
  				   glm::vec4(1, 1, 1, 1), bomb2Key);
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

  bool		PauseState::_initializeOptionAudioMenu()
  {
    Menu* menu = new Menu("audio", this);
    if (!menu->initialize())
      return (false);
    try
      {
	menu->createNewToggleButton("sound", NULL, glm::vec4(1, 1, 1, 1),
				    SoundManager::getInstance()->soundPlaying());
	menu->createNewToggleButton("music", NULL, glm::vec4(1, 1, 1, 1),
				    SoundManager::getInstance()->musicPlaying());
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

  bool		PauseState::_initializeOptionsMenu()
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

  void		PauseState::initialize()
  {
    std::vector<InputConfig*> configs;
    std::list<Player*>::iterator it;
    std::list<Player*> players = this->_gameState.getPlayerList();
    PlayerConfig playerConfig;
    for (it = players.begin(); it != players.end(); it++)
      {
	playerConfig = (*it)->getPlayerConfig();
	configs.push_back(playerConfig.inputConfig);
      }
    InputConfig* tab[4];
    memset(tab, 0, 4 * sizeof(*tab));
    int nb = 0;
    for (std::vector<InputConfig*>::iterator it = configs.begin();
	 it != configs.end(); it++)
      {
	tab[nb] = (*it);
	nb++;
      }
    if (tab[0])
      this->_inputConfigPlayer1 = tab[0];
    else
      {
	this->_inputConfigPlayer1 = new InputConfig();
	this->_inputConfigPlayer1->load(INPUT_CONFIG_P1);
      }
    if (tab[1])
      this->_inputConfigPlayer2 = tab[1];
    else
      {
	this->_inputConfigPlayer2 = new InputConfig();
	this->_inputConfigPlayer2->load(INPUT_CONFIG_P2);
      }
    if (tab[2])
      this->_inputConfigPlayer3 = tab[2];
    else
      {
	this->_inputConfigPlayer3 = new InputConfig();
	this->_inputConfigPlayer3->load(INPUT_CONFIG_P3);
      }
    if (tab[3])
      this->_inputConfigPlayer4 = tab[3];
    else
      {
	this->_inputConfigPlayer4 = new InputConfig();
	this->_inputConfigPlayer4->load(INPUT_CONFIG_P4);
      }
    this->_initializePauseMainMenu();
    this->_initializeOptionsMenu();
    this->_skybox = new Skybox();
    try
      {
	this->_skybox->initialize();
      }
    catch (FileLoadingException e)
      {
	std::cerr << "PauseState : Error initializing skybox" << std::endl;
      }
  }

  void		PauseState::_setBindingControlPlayer1(Menu* menu,
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

  void		PauseState::_setBindingControlPlayer2(Menu* menu,
  						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
  	 it != this->_SDLInputsList.end(); it++)
      {
  	if ((*it) != first)
  	  menu->addStateToLastButton(*it);
      }
  }

  void		PauseState::_setBindingControlPlayer3(Menu* menu,
  						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
  	 it != this->_SDLInputsList.end(); it++)
      {
  	if ((*it) != first)
  	  menu->addStateToLastButton(*it);
      }
  }

  void		PauseState::_setBindingControlPlayer4(Menu* menu,
  						     const std::string& first)
  {
    for (std::list<std::string>::iterator it = this->_SDLInputsList.begin();
  	 it != this->_SDLInputsList.end(); it++)
      {
  	if ((*it) != first)
  	  menu->addStateToLastButton(*it);
      }
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
    this->_skybox->update();
    this->_currentMenu->update(input);
  }

  void		PauseState::draw(float time, Screen& context)
  {
    Transform	perspective = ProjectionPerspective(60,
						    context.getSize().x /
						    context.getSize().y, 1.0f,
						    1000);
    Transform	camera = Camera(glm::vec3(10, 0, 0),
				glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    RenderState	state(perspective, camera);

    (void)time;
    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x,
					       context.getSize().y));
    context.clear();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    context.draw(*this->_skybox, state);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    context.draw(*this->_currentMenu, state);
    context.flush();
  }

  void		PauseState::setOptionControlPlayer1(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer1");
  }

  void		PauseState::setOptionControlPlayer2(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer2");
  }

  void		PauseState::setOptionControlPlayer3(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer3");
  }

  void		PauseState::setOptionControlPlayer4(Menu*)
  {
    this->_setNewCurrentMenu("controlplayer4");
  }

  void		PauseState::setOptionsAudioMenu(Menu*)
  {
    this->_setNewCurrentMenu("audio");
  }

  void		PauseState::setOptionsControlMenu(Menu*)
  {
    this->_setNewCurrentMenu("control");
  }

  void		PauseState::revealing() {}

  void		PauseState::saveGame(Menu*)
  {
    std::stringstream	ss;
    time_t		now = time(0);
    struct tm		tstruct;
    char		buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d_%m_%Y-%X", &tstruct);
    ss << buf;
    _gameState.save(ss.str());
    this->_manager.pop();
    this->_manager.pop();
    if (SoundManager::getInstance()->musicPlaying())
      {
	SoundManager::getInstance()->stop("theme");
	SoundManager::getInstance()->playMusic("menu");
      }
  }

  void		PauseState::resumeGame(Menu*)
  {
    this->_inputConfigPlayer1->load(INPUT_CONFIG_P1);
    this->_inputConfigPlayer2->load(INPUT_CONFIG_P2);
    this->_inputConfigPlayer3->load(INPUT_CONFIG_P3);
    this->_inputConfigPlayer4->load(INPUT_CONFIG_P4);
    this->_manager.pop();
    delete (this);
  }

  void		PauseState::setPlayMenu(Menu*)
  {
  }

  void		PauseState::setOptionsMenu(Menu*)
  {
    this->_setNewCurrentMenu("options");
  }

  void		PauseState::setHighScoreMenu(Menu*)
  {
  }

  void		PauseState::exitGame(Menu*)
  {
    SoundManager::getInstance()->stop("theme");
    SoundManager::getInstance()->playMusic("menu");
    this->_manager.pop();
    this->_manager.pop();
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
    this->_setNewCurrentMenu("pausemainmenu");
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

  void		PauseState::setMapParamsMenu(Menu*)
  {
  }

  void		PauseState::serializeBindingPlayer1(Menu* menu)
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

  void		PauseState::serializeBindingPlayer2(Menu* menu)
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

  void		PauseState::serializeBindingPlayer3(Menu* menu)
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

  void		PauseState::serializeBindingPlayer4(Menu* menu)
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

  void		PauseState::serializeAudioSettings(Menu* menu)
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
		this->_config->sound = s->isChecked();
		if (s->isChecked())
		  SoundManager::getInstance()->enableSounds();
		else
		  SoundManager::getInstance()->disableSounds();
	      }
	    else
	      {
		this->_config->music = s->isChecked();
		if (this->_config->music)
		  SoundManager::getInstance()->playMusic("theme");
		else
		  {
		    SoundManager::getInstance()->disableMusics();
		    SoundManager::getInstance()->stop("theme");
		  }
	      }
	    i++;
	  }
      	it++;
      }
    this->setOptionsMenu(menu);
  }

  PauseState::~PauseState()
  {
    delete (this->_skybox);
    for (std::list<Menu*>::iterator it = this->_menuList.begin();
	 it != this->_menuList.end(); it++)
      delete (*it);
  }
}
