#ifndef EVENTLISTENER_HH
#define EVENTLISTENER_HH

namespace bbm
{
  class	Input;

  class	IEventListener
  {
  public:
    virtual ~IEventListener() {}

    virtual void	handleEvents(float time, const Input& input) = 0;
  };
};

#endif /* EVENTLISTENER_HH */
