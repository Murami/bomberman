#ifndef GAME_HH
#define GAME_HH

#include <SdlContext.hh>
#include "events/Input.hh"
#include "game/GameManager.hh"

namespace bbm
{
  class Game
  {
  private:
    GameManager		_manager;
    Screen		_screen;
    Input		_input;

  public:
    Game();
    ~Game();

    int		run();
  };
};

#endif /* GAME_HH */
