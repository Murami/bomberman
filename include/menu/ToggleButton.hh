//
// ToggleButton.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 10:32:08 2014 Manu
// Last update Sun Jun  8 01:24:44 2014 Manu
//

#ifndef		__TOGGLEBUTTON_HH__
# define	__TOGGLEBUTTON_HH__

# include	<iostream>
# include	<list>
# include	<string>
# include	"AButton.hh"
# include	"Letter.hh"

namespace	bbm
{
  class		ARenderer;
  class		RenderState;

  class		ToggleButton : public AButton
  {
  private :
    std::list<Letter*>	_on;
    std::list<Letter*>	_off;
    bool		_checked;

  public :
    virtual bool	initialize();
    virtual void	draw(ARenderer&, const RenderState&);
    virtual void	translateButton(const glm::vec3&);
    virtual bool	onClick();
    virtual void	nextState();
    virtual void	prevState();

  public :
    void		setChecked(bool);

  public :
    bool		isChecked() const;

  public :
    ToggleButton(const std::string&, const glm::vec4&, bool checked = false);
    ~ToggleButton();
  };
}

#endif
