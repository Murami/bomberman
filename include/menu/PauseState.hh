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
# include	"game/GameLoadingState.hh"

namespace	bbm
{
  class		Input;
  class		GameManager;
  class		Skybox;
  class		InputConfig;
  class		GameState;

  class		PauseState : public IGameState, IMenuManager
  {

  public :
    const static std::string		INPUT_CONFIG_P1;
    const static std::string		INPUT_CONFIG_P2;
    const static std::string		INPUT_CONFIG_P3;
    const static std::string		INPUT_CONFIG_P4;

  private :
    GameManager&			_manager;
    GameState&				_gameState;
    Menu*				_currentMenu;
    std::list<Menu*>			_menuList;
    Skybox*				_skybox;
    GameLoadingState::GameConfig	_config;
    InputConfig*			_inputConfigPlayer1;
    InputConfig*			_inputConfigPlayer2;
    InputConfig*			_inputConfigPlayer3;
    InputConfig*			_inputConfigPlayer4;

  private :
    void			_setNewCurrentMenu(const std::string&);
    bool			_initializePauseMainMenu();
    bool			_initializeOptionsMenu();
    bool			_initializeOptionControlMenu();
    bool			_initializeOptionAudioMenu();
    bool			_initializeControlPlayer();
    bool			_initializeControlPlayer1();
    bool			_initializeControlPlayer2();
    bool			_initializeControlPlayer3();
    bool			_initializeControlPlayer4();
    void			_setBindingControlPlayer1(Menu*,
							  const std::string&);
    void			_setBindingControlPlayer2(Menu*,
							  const std::string&);
    void			_setBindingControlPlayer3(Menu*,
							  const std::string&);
    void			_setBindingControlPlayer4(Menu*,
							  const std::string&);
    const std::string&		_getKeyFromSDLK(const std::string&);

  public :
    virtual void		initialize();
    virtual void		release();
    virtual void		obscuring();
    virtual void		update(float time, const Input& input);
    virtual void		draw(float time, Screen& context);
    virtual void		revealing();

  public :
    virtual void		setPlayMenu(Menu*);
    virtual void		setOptionsMenu(Menu*);
    virtual void		setHighScoreMenu(Menu*);
    virtual void		exitGame(Menu*);
    virtual void		setNewGameMenu(Menu*);
    virtual void		setContinueGameMenu(Menu*);
    virtual void		setLoadGameMenu(Menu*);
    virtual void		setMainMenu(Menu*);
    virtual void		setOptionsAudioMenu(Menu*);
    virtual void		setOptionsControlMenu(Menu*);
    virtual void		setNextFrame(Menu*);
    virtual void		setPrevFrame(Menu*);
    virtual void		setIASelectionMenu(Menu*);
    virtual void		launchNewGame(Menu*);
    virtual void		launchLoadedGame(Menu*);
    virtual void		setOptionControlPlayer1(Menu*);
    virtual void		setOptionControlPlayer2(Menu*);
    virtual void		setOptionControlPlayer3(Menu*);
    virtual void		setOptionControlPlayer4(Menu*);
    virtual void		setMapParamsMenu(Menu*);
    virtual void		serializeBindingPlayer1(Menu*);
    virtual void		serializeBindingPlayer2(Menu*);
    virtual void		serializeBindingPlayer3(Menu*);
    virtual void		serializeBindingPlayer4(Menu*);
    virtual void		serializeAudioSettings(Menu*);

  public :
    virtual void		resumeGame(Menu*);
    virtual void	       	saveGame(Menu*);

  public :
    PauseState(GameManager&, GameState&);
    virtual ~PauseState();
  };
}

#endif
