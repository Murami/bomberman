#ifndef GAMELOADINGSTATE_HH
#define GAMELOADINGSTATE_HH

#include "game/IGameState.hh"

namespace bbm
{
  struct GameLoadingStateConfig
  {
  };

  class GameLoadingState : public IGamesState
  {
  public:
    GameLoadingState(GameManager& gameManager, const GameLoadingStateConfig& config);
    ~GameLoadingState();

    void	initialize();
    void	release();
    void	obscuring();
    void	update(float time, const Input& input);
    void	draw(float time, Screen& context);
    void	revealing();

  private:
    GameState&			_gameState;
  };
};

#endif /* GAMELOADINGSTATE_HH */
