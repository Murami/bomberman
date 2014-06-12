//
// IMenuManager.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 16:17:50 2014 Manu
// Last update Thu Jun 12 17:04:17 2014 Manu
//

#ifndef		__IMENUMANAGER_HH__
# define	__IMENUMANAGER_HH__

namespace	bbm
{
  class		Menu;
  class		IMenuManager
  {
  public :
    virtual void	setPlayMenu(Menu*) = 0;
    virtual void	setOptionsMenu(Menu*) = 0;
    virtual void	setHighScoreMenu(Menu*) = 0;
    virtual void	exitGame(Menu*) = 0;
    virtual void	setNewGameMenu(Menu*) = 0;
    virtual void	setContinueGameMenu(Menu*) = 0;
    virtual void	setLoadGameMenu(Menu*) = 0;
    virtual void	setMainMenu(Menu*) = 0;
    virtual void	setOptionsAudioMenu(Menu*) = 0;
    virtual void	setOptionsControlMenu(Menu*) = 0;
    virtual void	setNextFrame(Menu*) = 0;
    virtual void	setPrevFrame(Menu*) = 0;
    virtual void	setIASelectionMenu(Menu*) = 0;
    virtual void	launchNewGame(Menu*) = 0;
    virtual void	launchLoadedGame(Menu*) = 0;
    virtual void	setOptionControlPlayer1(Menu*) = 0;
    virtual void	setOptionControlPlayer2(Menu*) = 0;
    virtual void	setOptionControlPlayer3(Menu*) = 0;
    virtual void	setOptionControlPlayer4(Menu*) = 0;
    virtual void	setMapParamsMenu(Menu*) = 0;
    virtual void	serializeBindingPlayer1(Menu*) = 0;
    virtual void	serializeBindingPlayer2(Menu*) = 0;
    virtual void	serializeBindingPlayer3(Menu*) = 0;
    virtual void	serializeBindingPlayer4(Menu*) = 0;
    virtual void	serializeAudioSettings(Menu*) = 0;

  public :
    virtual void	resumeGame(Menu*) = 0;
    virtual void	saveGame(Menu*) = 0;

  };
}

#endif
