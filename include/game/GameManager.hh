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
