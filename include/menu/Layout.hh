//
// Layout.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 14:00:10 2014 Manu
// Last update Sat May 31 10:56:01 2014 Manu
//

#ifndef		__LAYOUT_HH__
# define	__LAYOUT_HH__

# include	<list>
# include	"AObject.hh"
# include	"Button.hh"

class		Menu;
class		Button;

class		Layout : public AObject
{
private :
  std::list<Button*>	_buttons;

public :
  virtual bool	initialize();
  virtual void	update(const gdl::Clock&, gdl::Input&);
  virtual void	draw(gdl::AShader&, const gdl::Clock&);

public :
  void		addButton(Button*);

public :
  Layout();
  ~Layout();
};

#endif
