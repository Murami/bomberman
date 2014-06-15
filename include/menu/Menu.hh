//
// Menu.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 10:53:00 2014 Manu
// Last update Sun Jun 15 23:23:56 2014 Manu
//

#ifndef		__MENU_HH__
# define	__MENU_HH__

# include	<string>
# include	"AObject.hh"
# include	"Button.hh"
# include	"StateButton.hh"
# include	"ToggleButton.hh"
# include	"Selector.hh"
# include	"IMenuManager.hh"
# include	"graphic/IDrawable.hh"
# include	"events/Input.hh"
# include	"Image.hh"

namespace	bbm
{
  class		Button;
  class		MenuManager;
  class		ARenderer;
  class		RenderState;
  class		Frame;
  class		FileExplorer;
  class		AButton;
  class		Letter;

  class		Menu : public IDrawable
  {
  private :
    const std::string				_title;
    IMenuManager*				_manager;
    std::list<void (IMenuManager::*)(Menu*)>	_callbacks;
    std::list<void (IMenuManager::*)(Menu*)>	_togglecallbacks;
    std::list<AButton*>				_buttons;
    AButton*					_frameTitle;
    int						_selected;
    Selector*					_selector;
    Frame*					_frame;
    std::list<Letter*>				_titleLetters;
    std::vector<std::vector<Letter*> >		_strings;

  private :
    void	_handleKeyDown(const Input&);
    void	_handleKeyUp(const Input&);
    void	_handleKeyReturn(const Input&);
    void	_handleKeyRight(const Input&);
    void	_handleKeyLeft(const Input&);
    std::vector<int>&	_sortScores(const std::vector<int>&);

  public :
    const std::string&		getTitle() const;
    const std::list<AButton*>&	getButtons() const;

  public :
    virtual void	draw(ARenderer&, const RenderState&);

  public :
    bool	initialize();
    void	update(const Input&);

  public :
    FileExplorer*	getExplorer();

  public :
    void	createNewButton(const std::string&,
				void (IMenuManager::*)(Menu*),
				const glm::vec4& v =
				glm::vec4(1, 1, 1, 1),
				bool clickable = false);
    void	createNewToggleButton(const std::string&,
				      void (IMenuManager::*)(Menu*),
				      const glm::vec4& v =
				      glm::vec4(1, 1, 1, 1),
				      bool state = false);
    void	createNewStateButton(const std::string& label,
				     void (IMenuManager::*)(Menu*),
				     size_t spaces = 2,
				     const glm::vec4& color =
				     glm::vec4(1, 1, 1, 1),
				     const std::string& def = "default");
    void	addStateToLastButton(const std::string&);
    void	createNewString(const std::string&);
    void	removeStateFromLastButton(const std::string&);
    void	createFrame();
    void	finalize();
    void	setNextFrame();
    void	setPrevFrame();
    void	refresh();

  public :
    Menu(const std::string&, IMenuManager*);
    ~Menu();
  };
}

#endif
