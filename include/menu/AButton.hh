//
// AButton.hh for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 11:51:04 2014 Manu
// Last update Wed Jun 11 14:56:52 2014 Manu
//

#ifndef		__ABUTTON_HH__
# define	__ABUTTON_HH__

# include	<string>
# include	<list>
# include	"AObject.hh"
# include	"glm/glm.hpp"
# include	"glm/gtc/matrix_transform.hpp"

namespace	bbm
{
  class		Letter;
  class		ARenderer;
  class		RenderState;

  class		AButton : public AObject
  {
  protected :
    const std::string	_label;
    std::list<Letter*>	_letters;
    const glm::vec4&	_color;
    bool		_useCallback;
    std::string		_type;
    bool		_selectable;

  public :
    void		setSelectable(bool);
    bool		isSelectable() const;

  public :
    size_t		getSize() const;
    const std::string&	getLabel() const;

  public :
    virtual bool	onClick() = 0;
    virtual void	nextState() = 0;
    virtual void	prevState() = 0;

  public :
    bool	useCallback() const;
    const std::string&	getType() const;

  public :
    virtual void	translateButton(const glm::vec3&) = 0;
    virtual bool	initialize() = 0;
    virtual void	draw(ARenderer&, const RenderState&) = 0;

  public :
    AButton(const std::string&, const glm::vec4&, bool, const std::string&);
    ~AButton();
  };
}

#endif
