//
// GameManager.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:15 2014 otoshigami
// Last update Sun Jun 15 08:36:16 2014 otoshigami
//

#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <stack>
#include <vector>

namespace bbm
{
  class	IGameState;
  class Input;
  class Screen;

  class GameManager
  {
  private:
    typedef std::vector<IGameState*>::iterator	StateListIt;

    std::vector<IGameState*>	_states;

  public:
    GameManager();
    ~GameManager();

    void		set(IGameState* state);
    void		push(IGameState* state);
    void       		pop();
    IGameState*		top();
    void		update(float time, const Input& input);
    void		draw(float time, Screen& context);
  };
};

#endif /* GAMEMANAGER_HH */
