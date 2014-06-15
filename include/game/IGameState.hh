//
// IGameState.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:31 2014 otoshigami
// Last update Sun Jun 15 08:36:32 2014 otoshigami
//

#ifndef IGAMESTATE_HH
# define IGAMESTATE_HH

namespace bbm
{
  class Screen;
  class	Input;

  class IGameState
  {
  public:
    virtual ~IGameState() {}

    virtual void	initialize() = 0;
    virtual void	release() = 0;
    virtual void	obscuring() = 0;
    virtual void	update(float time, const Input& input) = 0;
    virtual void	draw(float time, Screen& context) = 0;
    virtual void	revealing() = 0;
  };
};

#endif /* IGAMESTATE_HH */
