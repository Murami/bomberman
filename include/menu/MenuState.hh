//
// MenuState.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 16:43:06 2014 Manu
// Last update Tue Jun 10 19:28:19 2014 Manu
//

#ifndef		__MENUSTATE_HH__
# define	__MENUSTATE_HH__

# include	<sstream>
# include	<sys/types.h>
# include	<dirent.h>
# include	<iostream>
# include	<string>
# include	<list>
# include	"Skybox.hh"
# include	"Menu.hh"
# include	"IMenuManager.hh"
# include	"game/IGameState.hh"
# include	"game/GameState.hh"
# include	"menu/Skybox.hh"

namespace	bbm
{
  class		Input;
  class		GameManager;

  class		MenuState : public IGameState, IMenuManager
  {
  private :
    GameManager&	_manager;
    Skybox		_skybox;
    Menu*		_currentMenu;
    std::list<Menu*>	_menuList;

  private :
    bool		_initializeMainMenu();
    bool		_initializePlayMenu();
    bool		_initializeMatchmakingMenu();
    bool		_initializeOptionsMenu();
    bool		_initializeHighscoresMenu();
    bool		_initializePlayerSelectionMenu();
    bool		_initializeIASelection1Menu();
    bool		_initializeIASelection2Menu();
    bool		_initializeIASelection3Menu();
    bool		_initializeIASelection4Menu();
    bool		_initializeLoadGameMenu();
    bool		_initializeOptionControlMenu();
    bool		_initializeOptionAudioMenu();
    bool		_initializeOptionVideoMenu();
    bool		_initializeControlPlayer1();
    bool		_initializeControlPlayer2();
    bool		_initializeMapParamsMenu();

  private :
    void		_setNewCurrentMenu(const std::string&);
    void		_setBindingControlPlayer1(Menu*, const std::string&);
    void		_setBindingControlPlayer2(Menu*, const std::string&);

  public :
    virtual void	initialize();
    virtual void	release();
    virtual void	obscuring();
    virtual void	update(float time, const Input& input);
    virtual void	draw(float time, Screen& context);
    virtual void	revealing();

  public :
    virtual void	setPlayMenu();
    virtual void	setOptionsMenu();
    virtual void	setHighScoreMenu();
    virtual void	exitGame();
    virtual void	setNewGameMenu();
    virtual void	setContinueGameMenu();
    virtual void	setLoadGameMenu();
    virtual void	setMainMenu();
    virtual void	setOptionsAudioMenu();
    virtual void	setOptionsControlMenu();
    virtual void	setNextFrame();
    virtual void	setPrevFrame();
    virtual void	setIASelection1Menu();
    virtual void	setIASelection2Menu();
    virtual void	setIASelection3Menu();
    virtual void	setIASelection4Menu();
    virtual void	launchNewGame();
    virtual void	setOptionControlPlayer1();
    virtual void	setOptionControlPlayer2();
    virtual void	setMapParamsMenu();

  public :
    MenuState(GameManager&);
    virtual ~MenuState();
  };
}

#endif
