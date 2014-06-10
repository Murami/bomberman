//
// MenuManager.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_4
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu May 15 12:13:33 2014 Manu
// Last update Tue Jun  3 17:04:57 2014 Manu
//

#include		"MenuManager.hh"

MenuManager::MenuManager() : AObject()
{
}

bool		MenuManager::initialize()
{
  if (!this->_background.initialize())
    return (false);
  this->_initializeMainMenu();
  this->_initializeCampaignMenu();
  this->_initializeMatchmakingMenu();
  this->_initializeOptionsMenu();
  this->_initializeHighscoresMenu();
  return (true);
}

bool		MenuManager::_initializeMainMenu()
{
  Menu* menu = new Menu("bomberman", 0, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("campaign", &IMenuManager::setCampaignMenu);
  menu->createNewButton("matchmaking", &IMenuManager::setMatchmakingMenu);
  menu->createNewButton("options", &IMenuManager::setOptionsMenu);
  menu->createNewButton("highscores", &IMenuManager::setHighScoreMenu);
  menu->createNewButton("exit", &IMenuManager::exitGame, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_currentMenu = menu;
  this->_menuList.push_back(menu);
  return (true);
}

bool		MenuManager::_initializeCampaignMenu()
{
  Menu* menu = new Menu("campaign", 1, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("new", &IMenuManager::setNewCampaignMenu);
  menu->createNewButton("continue", &IMenuManager::setContinueCampaignMenu);
  menu->createNewButton("load", &IMenuManager::setLoadCampaignMenu);
  menu->createNewButton("back", &IMenuManager::setMainMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);
  return (true);
}

bool		MenuManager::_initializeMatchmakingMenu()
{
  Menu* menu = new Menu("matchmaking", 2, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("create", &IMenuManager::setCreateRoomMenu);
  menu->createNewButton("join", &IMenuManager::setJoinRoomMenu);
  menu->createNewButton("back", &IMenuManager::setMainMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);
  return (true);
}

bool		MenuManager::_initializeOptionsMenu()
{
  Menu* menu = new Menu("options", 3, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("video", &IMenuManager::setOptionsVideoMenu);
  menu->createNewButton("audio", &IMenuManager::setOptionsAudioMenu);
  menu->createNewButton("control", &IMenuManager::setOptionsControlMenu);
  menu->createNewButton("back", &IMenuManager::setMainMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);

  menu = new Menu("control", 5, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("go up", &IMenuManager::setMainMenu);
  menu->createNewButton("go down", &IMenuManager::setMainMenu);
  menu->createNewButton("go left", &IMenuManager::setMainMenu);
  menu->createNewButton("go right", &IMenuManager::setMainMenu);
  menu->createNewButton("drop bomb", &IMenuManager::setMainMenu);
  menu->createNewButton("ok", &IMenuManager::setOptionsMenu, glm::vec4(0, 1, 0, 1));
  menu->createNewButton("cancel", &IMenuManager::setOptionsMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);

  menu = new Menu("audio", 6, this);
  if (!menu->initialize())
    return (false);
  menu->createNewToggleButton("sound", &IMenuManager::setMainMenu);
  menu->createNewToggleButton("music", &IMenuManager::setMainMenu);
  menu->createNewButton("ok", &IMenuManager::setOptionsMenu, glm::vec4(0, 1, 0, 1));
  menu->createNewButton("cancel", &IMenuManager::setOptionsMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);

  menu = new Menu("video", 7, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("resolution", &IMenuManager::setMainMenu);
  menu->createNewButton("ok", &IMenuManager::setOptionsMenu, glm::vec4(0, 1, 0, 1));
  menu->createNewButton("cancel", &IMenuManager::setOptionsMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);

  return (true);
}

bool		MenuManager::_initializeHighscoresMenu()
{
  Menu* menu = new Menu("highscores", 4, this);
  if (!menu->initialize())
    return (false);
  menu->createNewButton("back", &IMenuManager::setMainMenu, glm::vec4(1, 0, 0, 1));
  menu->finalize();
  this->_menuList.push_back(menu);
  return (true);
}

void		MenuManager::_setNewCurrentMenu(const std::string& name, int id)
{
  std::list<Menu*>::iterator it = this->_menuList.begin();
  while (it != this->_menuList.end())
    {
      if ((*it)->getTitle() == name && (*it)->getId() == id)
	{
	  this->_currentMenu = (*it);
	  this->_currentMenu->initialize();
	  break;
	}
      it++;
    }
}

void		MenuManager::setOptionsVideoMenu()
{
  std::cout << "set options video menu" << std::endl;
  this->_setNewCurrentMenu("video", 7);
}

void		MenuManager::setOptionsAudioMenu()
{
  std::cout << "set options audio menu" << std::endl;
  this->_setNewCurrentMenu("audio", 6);
}

void		MenuManager::setOptionsControlMenu()
{
  std::cout << "set options control menu" << std::endl;
  this->_setNewCurrentMenu("control", 5);
}

void		MenuManager::setCreateRoomMenu()
{
  std::cout << "set create room menu" << std::endl;
}

void		MenuManager::setJoinRoomMenu()
{
  std::cout << "set join room menu" << std::endl;
}

void		MenuManager::setMainMenu()
{
  this->_currentMenu = (*(this->_menuList.begin()));
  this->_currentMenu->initialize();
}

void		MenuManager::setLoadCampaignMenu()
{
  std::cout << "set load campaign menu" << std::endl;
}

void		MenuManager::setContinueCampaignMenu()
{
  std::cout << "set continue campaign menu" << std::endl;
}

void		MenuManager::setNewCampaignMenu()
{
  std::cout << "set new campaign menu" << std::endl;
}

void		MenuManager::setCampaignMenu()
{
  this->_setNewCurrentMenu("campaign", 1);
  std::cout << "Setting campaign menu" << std::endl;
}

void		MenuManager::setMatchmakingMenu()
{
  this->_setNewCurrentMenu("matchmaking", 2);
  std::cout << "Setting matchmaking menu" << std::endl;
}

void		MenuManager::setOptionsMenu()
{
  this->_setNewCurrentMenu("options", 3);
  std::cout << "Setting options menu" << std::endl;
}

void		MenuManager::setHighScoreMenu()
{
  this->_setNewCurrentMenu("highscores", 4);
  std::cout << "Setting high score menu" << std::endl;
}

void		MenuManager::exitGame()
{
  std::cout << "Exit game" << std::endl;
  exit(0);
}

void		MenuManager::update(const gdl::Clock& clock, gdl::Input& input)
{
  this->_background.update(clock, input);
  this->_currentMenu->update(clock, input);
}

void		MenuManager::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  this->_background.draw(shader, clock);
  this->_currentMenu->draw(shader, clock);
}

MenuManager::~MenuManager()
{
}
