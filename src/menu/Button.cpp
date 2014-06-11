//
// Button.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 11:33:46 2014 Manu
// Last update Wed Jun 11 03:39:08 2014 Manu
//

#include		"Button.hh"

namespace	bbm
{

  Button::Button(const std::string& label,
		 const glm::vec4& color, bool clickable) : AButton(label, color, clickable, "button")
  {
  }

  void		Button::nextState()
  {
  }

  void		Button::prevState()
  {
  }

  bool		Button::onClick()
  {
    return (false);
  }

  bool		Button::initialize()
  {
    for (size_t i = 0; i < this->_label.size(); i++)
      {
	Letter* l = new Letter(this->_label[i], this->_color);
	l->initialize();
	this->_letters.push_back(l);
      }
    size_t i = 0;
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end();
	 it++)
      {
	(*it)->translate(glm::vec3(0, 0,
				   static_cast<float>(6 -
						      static_cast<float>(i)/2)));
	i++;
      }
    return (true);
  }

  void		Button::translateButton(const glm::vec3& pos)
  {
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end(); it++)
      (*it)->translate(pos);
  }

  void		Button::draw(ARenderer& r, const RenderState& s)
  {
    std::list<Letter*>::iterator it = this->_letters.begin();
    while (it != this->_letters.end())
      {
	(*it)->draw(r, s);
	it++;
      }
  }

  Button::~Button()
  {
  }

}