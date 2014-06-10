#ifndef GAMELOADINGSTATE_HH
#define GAMELOADINGSTATE_HH

#include "game/IGameState.hh"

namespace bbm
{
  class GameManager;

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

  private:
    void	loadShader();
    void	loadTexture();
    void	loadSound();
    void	loadModel();

  private:
    bool			_loading;
    GameManager&			_manager;
  };
};

#endif /* GAMELOADINGSTATE_HH */
