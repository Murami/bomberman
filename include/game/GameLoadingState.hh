#ifndef GAMELOADINGSTATE_HH
#define GAMELOADINGSTATE_HH

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

  private:
    bool				_finish;
    Object*				_loading;
    Object*				_loadingFinished;
    GameManager&			_manager;
  };
};

#endif /* GAMELOADINGSTATE_HH */
