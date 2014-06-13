#include		"game/GameManager.hh"
#include		"PauseState.hh"

namespace		bbm
{
  const std::string	PauseState::INPUT_CONFIG_P1 = "./inputConfig1.json";
  const std::string	PauseState::INPUT_CONFIG_P2 = "./inputConfig2.json";
  const std::string	PauseState::INPUT_CONFIG_P3 = "./inputConfig3.json";
  const std::string	PauseState::INPUT_CONFIG_P4 = "./inputConfig4.json";

  PauseState::PauseState(GameManager& manager) :
    _manager(manager)
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
	std::cout << "Return '" << newKey << "'" << std::endl;
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
	menu->createNewButton("save", &IMenuManager::saveGame,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("options", &IMenuManager::setOptionsMenu,
			      glm::vec4(1, 1, 1, 1), true);
	menu->createNewButton("quit", &IMenuManager::exitGame,
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

  bool		PauseState::_initializeControlPlayer1()
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
	this->_setBindingControlPlayer1(menu, "UP");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("down")));
	this->_setBindingControlPlayer1(menu, "DOWN");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("left")));
	this->_setBindingControlPlayer1(menu, "LEFT");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("right")));
	this->_setBindingControlPlayer1(menu, "RIGHT");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb")));
	this->_setBindingControlPlayer1(menu, "SPACE");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer1->getKeyName("bomb2")));
	this->_setBindingControlPlayer1(menu, "RETURN");
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
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("up")));
	this->_setBindingControlPlayer2(menu, "z");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("down")));
	this->_setBindingControlPlayer2(menu, "s");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("left")));
	this->_setBindingControlPlayer2(menu, "q");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("right")));
	this->_setBindingControlPlayer2(menu, "d");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb")));
	this->_setBindingControlPlayer2(menu, "x");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer2->getKeyName("bomb2")));
	this->_setBindingControlPlayer2(menu, "w");
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
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("up")));
	this->_setBindingControlPlayer2(menu, "z");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("down")));
	this->_setBindingControlPlayer2(menu, "s");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("left")));
	this->_setBindingControlPlayer2(menu, "q");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("right")));
	this->_setBindingControlPlayer2(menu, "d");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb")));
	this->_setBindingControlPlayer2(menu, "x");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer3->getKeyName("bomb2")));
	this->_setBindingControlPlayer2(menu, "w");
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
	menu->createNewStateButton("up", NULL, 7,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("up")));
	this->_setBindingControlPlayer2(menu, "z");
	menu->createNewStateButton("down", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("down")));
	this->_setBindingControlPlayer2(menu, "s");
	menu->createNewStateButton("left", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("left")));
	this->_setBindingControlPlayer2(menu, "q");
	menu->createNewStateButton("right", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("right")));
	this->_setBindingControlPlayer2(menu, "d");
	menu->createNewStateButton("bomb", NULL, 5,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb")));
	this->_setBindingControlPlayer2(menu, "x");
	menu->createNewStateButton("bomb2", NULL, 4,
				   glm::vec4(1, 1, 1, 1),
				   this->_getKeyFromSDLK(this->_inputConfigPlayer4->getKeyName("bomb2")));
	this->_setBindingControlPlayer2(menu, "w");
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
	menu->createNewToggleButton("sound", &IMenuManager::setMainMenu);
	menu->createNewToggleButton("music", &IMenuManager::setMainMenu);
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
    memset(&this->_config, 0, sizeof(this->_config));
    this->_initializePauseMainMenu();
    this->_initializeOptionsMenu();
    this->_inputConfigPlayer1 = new InputConfig();
    this->_inputConfigPlayer1->load(INPUT_CONFIG_P1);
    this->_inputConfigPlayer2 = new InputConfig();
    this->_inputConfigPlayer2->load(INPUT_CONFIG_P2);
    this->_inputConfigPlayer3 = new InputConfig();
    this->_inputConfigPlayer3->load(INPUT_CONFIG_P3);
    this->_inputConfigPlayer4 = new InputConfig();
    this->_inputConfigPlayer4->load(INPUT_CONFIG_P4);
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
    static std::list<std::string> list;
    if (list.size() == 0)
      {
	list.push_back("UP");
	list.push_back("DOWN");
	list.push_back("LEFT");
	list.push_back("RIGHT");
	list.push_back("0");
	list.push_back("1");
	list.push_back("RSHIFT");
	list.push_back("RCTRL");
	list.push_back("RETURN");
	list.push_back("SPACE");
      }
    for (std::list<std::string>::iterator it = list.begin();
    	 it != list.end(); it++)
      {
    	if ((*it) != first)
    	  menu->addStateToLastButton(*it);
      }
  }

  ////////////////////////////////////////////////////////
  // FAIRE LES BINDING POUR LES 2 DERNIERS KEYBOARDS //
  ////////////////////////////////////////////////////////

  void		PauseState::_setBindingControlPlayer2(Menu* menu,
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

  void		PauseState::_setBindingControlPlayer3(Menu* menu,
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

  void		PauseState::_setBindingControlPlayer4(Menu* menu,
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

  void		PauseState::revealing() {}
  void		PauseState::saveGame(Menu*) {}

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
	      this->_config.sound = s->isChecked();
	    else
	      this->_config.music = s->isChecked();
	    i++;
	  }
      	it++;
      }
    this->setOptionsMenu(menu);
  }

  PauseState::~PauseState()
  {
  }
}
