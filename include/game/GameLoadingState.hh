//
// GameLoadingState.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:12 2014 otoshigami
// Last update Sun Jun 15 08:36:12 2014 otoshigami
//

#ifndef GAMELOADINGSTATE_HH
#define GAMELOADINGSTATE_HH

#include <string>

#include "game/IGameState.hh"

namespace bbm
{
  class GameManager;
  class Object;

  class GameLoadingState : public IGameState
  {

  public :
    struct		GameConfig
    {
      int		mapSizeX;
      int		mapSizeY;
      int		nbPlayers;
      int		player1;
      int		player2;
      int		player3;
      int		player4;
      int		numberIA;
      int		level;
      bool		music;
      bool		sound;
      bool		newGame;
      std::string*	fileToLoad;
    };

  public:
    GameLoadingState(GameManager& gameManager, GameConfig* config);
    ~GameLoadingState();

    void	initialize();
    void	release();
    void	obscuring();
    void	update(float time, const Input& input);
    void	draw(float time, Screen& context);
    void	revealing();

  private:
    void	loadShader();
    void	loadTexture();
    void	loadSound();
    void	loadModel();
    void        loadGameState();
    void	newGameState();

  private:
    bool				_finish;
    Object*				_loading;
    Object*				_loadingFinished;
    GameManager&			_manager;
    GameConfig*				_config;
  };
};

#endif /* GAMELOADINGSTATE_HH */
