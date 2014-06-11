//
// StateButton.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 17:43:50 2014 Manu
// Last update Wed Jun 11 05:03:29 2014 Manu
//

#ifndef		__STATEBUTTON_HH__
# define	__STATEBUTTON_HH__

# include	<iostream>
# include	<string>
# include	<vector>
# include	"AButton.hh"

namespace	bbm
{
  class		ARenderer;
  class		RenderState;

  class		StateButton : public AButton
  {
  private :
    std::string				_currentState;
    std::vector<std::string>		_states;
    std::vector<std::vector<Letter*> >	_stateLetters;
    std::list<Letter*>			_letters;
    size_t				_index;
    size_t				_nbSpaces;

  public :
    const std::string&		getState();
    void			addState(const std::string&);
    void			removeState(const std::string&);
    void			setState(const std::string&);

  public :
    virtual bool		initialize();
    virtual void		draw(ARenderer&, const RenderState&);
    virtual void		translateButton(const glm::vec3&);
    virtual bool		onClick();
    virtual void		nextState();
    virtual void		prevState();

  public :
    StateButton(const std::string& label,
		size_t nbSpaces,
		const std::string& defaultState,
		const glm::vec4& color);
    ~StateButton();
  };
}

#endif
