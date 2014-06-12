#ifndef		__PAUSESTATE_HH__
# define	__PAUSESTATE_HH__

# include	<Texture.hh>
# include	"Menu.hh"
# include	"IMenuManager.hh"
# include	"game/IGameState.hh"
# include	"game/GameState.hh"
# include	"FileLoadingException.hh"
# include	"Image.hh"
# include	"game/GameState.hh"
# include	"graphic/ShaderManager.hh"
# include	"graphic/Camera.hh"

namespace	bbm
{
  class		Input;
  class		GameManager;
  class		GameState;

  class		PauseState : public IGameState, IMenuManager
  {
  public :
    static const std::string	PAUSE_BACKGROUND;

  private :
    GameManager&	_manager;
    Menu*		_currentMenu;
    std::list<Menu*>	_menuList;
    Image*		_image;
    GameState*		_gameState;

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
    PauseState(GameManager&, GameState*);
    virtual ~PauseState();
  };
}

#endif
