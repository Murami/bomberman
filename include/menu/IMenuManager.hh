//
// IMenuManager.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 16:17:50 2014 Manu
// Last update Mon Jun  9 16:51:36 2014 Manu
//

#ifndef		__IMENUMANAGER_HH__
# define	__IMENUMANAGER_HH__

namespace	bbm
{
  class		IMenuManager
  {
  public :
    virtual void	setPlayMenu() = 0;
    virtual void	setOptionsMenu() = 0;
    virtual void	setHighScoreMenu() = 0;
    virtual void	exitGame() = 0;
    virtual void	setNewGameMenu() = 0;
    virtual void	setContinueGameMenu() = 0;
    virtual void	setLoadGameMenu() = 0;
    virtual void	setMainMenu() = 0;
    virtual void	setOptionsAudioMenu() = 0;
    virtual void	setOptionsControlMenu() = 0;
    virtual void	setNextFrame() = 0;
    virtual void	setPrevFrame() = 0;
    virtual void	setIASelection1Menu() = 0;
    virtual void	setIASelection2Menu() = 0;
    virtual void	setIASelection3Menu() = 0;
    virtual void	setIASelection4Menu() = 0;
    virtual void	launchNewGame() = 0;
    virtual void	setOptionControlPlayer1() = 0;
    virtual void	setOptionControlPlayer2() = 0;
    virtual void	setMapParamsMenu() = 0;
  };
}

#endif
