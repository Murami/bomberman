//
// IntroState.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:49:50 2014 Manu
// Last update Sun Jun 15 11:49:51 2014 Manu
//

#ifndef		__INTROSTATE_HH__
# define	__INTROSTATE_HH__

# include	<iostream>
# include	"game/IGameState.hh"
# include	"graphic/Model.hh"
# include	"game/GameManager.hh"
# include	"menu/Skybox.hh"
# include	"menu/Image.hh"

namespace	bbm
{
  class		IntroState : public IGameState
  {
  public :
    const static std::string	SCREEN_PATH;
  private :
    Model*			_marvin;
    GameManager &		_manager;
    Skybox			_skybox;
    Image*			_screen;

  public :
    virtual void		initialize();
    virtual void		release();
    virtual void		obscuring();
    virtual void		update(float, const Input&);
    virtual void		draw(float, Screen&);
    virtual void		revealing();

  public :
    IntroState(GameManager&);
    virtual ~IntroState();

  };
}

#endif
