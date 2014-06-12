//
// MenuState.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 16:43:06 2014 Manu
// Last update Thu Jun 12 17:02:51 2014 Manu
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
# include	"game/GameLoadingState.hh"
# include	"events/InputConfig.hh"

namespace	bbm
{
  class		Input;
  class		GameManager;
  class		FileExplorer;

  class		MenuState : public IGameState, IMenuManager
  {
  public :
    const static std::string		INPUT_CONFIG_P1;
    const static std::string		INPUT_CONFIG_P2;
    const static std::string		INPUT_CONFIG_P3;
    const static std::string		INPUT_CONFIG_P4;

  private :
    GameManager&			_manager;
    Skybox				_skybox;
    Menu*				_currentMenu;
    std::list<Menu*>			_menuList;
    GameLoadingState::GameConfig	_config;
    InputConfig*			_inputConfigPlayer1;
    InputConfig*			_inputConfigPlayer2;
    InputConfig*			_inputConfigPlayer3;
    InputConfig*			_inputConfigPlayer4;

  private :
    bool		_initializeMainMenu();
    bool		_initializePlayMenu();
    bool		_initializeMatchmakingMenu();
    bool		_initializeOptionsMenu();
    bool		_initializeHighscoresMenu();
    bool		_initializePlayerSelectionMenu();
    bool		_initializeIASelectionMenu();
    bool		_initializeLoadGameMenu();
    bool		_initializeOptionVideoMenu();
    bool		_initializeOptionControlMenu();
    bool		_initializeOptionAudioMenu();
    bool		_initializeControlPlayer1();
    bool		_initializeControlPlayer2();
    bool		_initializeControlPlayer3();
    bool		_initializeControlPlayer4();
    bool		_initializeMapParamsMenu();
    bool		_initializeInputConfig();

  private :
    void		_setNewCurrentMenu(const std::string&);
    void		_setBindingControlPlayer1(Menu*, const std::string&);
    void		_setBindingControlPlayer2(Menu*, const std::string&);
    void		_setBindingControlPlayer3(Menu*, const std::string&);
    void		_setBindingControlPlayer4(Menu*, const std::string&);
    const std::string&	_getKeyFromSDLK(const std::string&);

  public :
    virtual void	initialize();
    virtual void	release();
    virtual void	obscuring();
    virtual void	update(float time, const Input& input);
    virtual void	draw(float time, Screen& context);
    virtual void	revealing();

  public :
    virtual void	setPlayMenu(Menu*);
    virtual void	setOptionsMenu(Menu*);
    virtual void	setHighScoreMenu(Menu*);
    virtual void	exitGame(Menu*);
    virtual void	setNewGameMenu(Menu*);
    virtual void	setContinueGameMenu(Menu*);
    virtual void	setLoadGameMenu(Menu*);
    virtual void	setMainMenu(Menu*);
    virtual void	setOptionsAudioMenu(Menu*);
    virtual void	setOptionsControlMenu(Menu*);
    virtual void	setNextFrame(Menu*);
    virtual void	setPrevFrame(Menu*);
    virtual void	setIASelectionMenu(Menu*);
    virtual void	launchNewGame(Menu*);
    virtual void	launchLoadedGame(Menu*);
    virtual void	setOptionControlPlayer1(Menu*);
    virtual void	setOptionControlPlayer2(Menu*);
    virtual void	setOptionControlPlayer3(Menu*);
    virtual void	setOptionControlPlayer4(Menu*);
    virtual void	setMapParamsMenu(Menu*);
    virtual void	serializeBindingPlayer1(Menu*);
    virtual void	serializeBindingPlayer2(Menu*);
    virtual void	serializeBindingPlayer3(Menu*);
    virtual void	serializeBindingPlayer4(Menu*);
    virtual void	serializeAudioSettings(Menu*);

  public :
    virtual void	resumeGame(Menu*);
    virtual void	saveGame(Menu*);

  public :
    MenuState(GameManager&);
    virtual ~MenuState();
  };
}

#endif
