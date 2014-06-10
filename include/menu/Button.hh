//
// Button.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 11:33:42 2014 Manu
// Last update Sun Jun  8 01:24:08 2014 Manu
//

#ifndef		__BUTTON_HH__
# define	__BUTTON_HH__

# include	<iostream>
# include	<list>
# include	<string>
# include	"AButton.hh"
# include	"Letter.hh"
# include	"FileLoadingException.hh"

namespace	bbm
{

  class		Menu;
  class		Layout;
  class		Input;
  class		RenderState;

  class		Button : public AButton
  {
  public :
    virtual bool	initialize();
    virtual void	draw(ARenderer&, const RenderState&);
    virtual void	translateButton(const glm::vec3&);
    virtual bool	onClick();
    virtual void	nextState();
    virtual void	prevState();

  public :
    Button(const std::string&, const glm::vec4&, bool clickable);
    ~Button();
  };
}

#endif
