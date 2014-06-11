#ifndef GAMELOADINGSTATE_HH
#define GAMELOADINGSTATE_HH

#include "game/IGameState.hh"

namespace bbm
{
  class GameManager;
  class Object;

  class GameLoadingState : public IGameState
  {
  public:
    GameLoadingState(GameManager& gameManager);
    ~GameLoadingState();

    void	initialize();
    void	release();
    void	obscuring();
    void	update(float time, const Input& input);
    void	draw(float time, Screen& context);
    void	revealing();

  public :
    struct		GameConfig
    {
      int		mapSizeX;
      int		mapSizeY;
      bool		player2;
      bool		player3;
      bool		player4;
      int		numberIA;
      int		level;
    };

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
