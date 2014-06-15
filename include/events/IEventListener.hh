//
// IEventListener.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:38:23 2014 otoshigami
// Last update Sun Jun 15 08:38:24 2014 otoshigami
//

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
