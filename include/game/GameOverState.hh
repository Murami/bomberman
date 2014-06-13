#ifndef GAMEOVERSTATE_HH
# define GAMEOVERSTATE_HH

# include <string>
# include <map>
# include "game/IGameState.hh"

namespace bbm
{
  class GameManager;
  class Object;

  class GameOverState : public IGameState
  {

  public:
    GameOverState(GameManager& gameManager, const std::string &);
    ~GameOverState();

    void					initialize();
    void					release();
    void					obscuring();
    void					update(float time, const Input& input);
    void					draw(float time, Screen& context);
    void					revealing();

  private:
    Object*					_screenOver;
    GameManager&				_manager;
  };
};

#endif /* GAMEOVERSTATE_HH */