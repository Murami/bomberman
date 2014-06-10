#ifndef		__PAUSESTATE_HH__
# define	__PAUSESTATE_HH__

# include	"Menu.hh"
# include	"IMenuManager.hh"
# include	"game/IGameState.hh"
# include	"game/GameState.hh"

namespace	bbm
{
  class		Input;
  class		GameManager;

  class		PauseState : public IGameState, IMenuManager
  {
  private :
    GameManager&	_manager;
    Menu*		_currentMenu;
    std::list<Menu*>	_menuList;

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
    PauseState(GameManager&);
    virtual ~PauseState();
  };
}

#endif
