
//
// MenuManager.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_4
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu May 15 12:13:30 2014 Manu
// Last update Tue Jun  3 16:27:51 2014 Manu
//

#ifndef		__MENUMANAGER_HH__
# define	__MENUMANAGER_HH__

# include	"Menu.hh"
# include	"MenuBackground.hh"
# include	"Skybox.hh"
# include	"IMenuManager.hh"

class		Menu;
class		Button;
class		Layout;

class		MenuManager : public AObject, IMenuManager
{
private :
  std::list<Menu*>	_menuList;
  Menu*			_currentMenu;
  Skybox		_background;

private :
  bool		_initializeMainMenu();
  bool		_initializeCampaignMenu();
  bool		_initializeMatchmakingMenu();
  bool		_initializeOptionsMenu();
  bool		_initializeHighscoresMenu();

public :
  MenuManager();
  ~MenuManager();

private :
  void		_setNewCurrentMenu(const std::string&, int);

public :
  virtual void		setCampaignMenu();
  virtual void		setMatchmakingMenu();
  virtual void		setOptionsMenu();
  virtual void		setHighScoreMenu();
  virtual void		exitGame();

  virtual void		setNewCampaignMenu();
  virtual void		setContinueCampaignMenu();
  virtual void		setLoadCampaignMenu();

  virtual void		setMainMenu();

  virtual void		setCreateRoomMenu();
  virtual void		setJoinRoomMenu();

  virtual void		setOptionsVideoMenu();
  virtual void		setOptionsAudioMenu();
  virtual void		setOptionsControlMenu();

public :
  bool		initialize();
  void		update(const gdl::Clock&, gdl::Input&);
  void		draw(gdl::AShader&, const gdl::Clock&);
};

#endif
