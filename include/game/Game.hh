//
// Game.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:07 2014 otoshigami
// Last update Sun Jun 15 08:36:08 2014 otoshigami
//

#ifndef GAME_HH
#define GAME_HH

#include <SdlContext.hh>

#include "graphic/Screen.hh"

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
