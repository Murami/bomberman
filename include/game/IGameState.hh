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
