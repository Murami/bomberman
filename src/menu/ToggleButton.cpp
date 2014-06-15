//
// ToggleButton.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue Jun  3 10:37:03 2014 Manu
// Last update Sun Jun 15 12:02:01 2014 Manu
//

#include		"sound/SoundManager.hh"
#include		"ToggleButton.hh"

namespace		bbm
{

  ToggleButton::ToggleButton(const std::string& label,
			     const glm::vec4& color,
			     bool checked) :
    AButton(label, color, true, "toggle")
  {
    this->_checked = checked;
  }

  void		ToggleButton::nextState()
  {
  }

  void		ToggleButton::prevState()
  {
  }

  bool		ToggleButton::onClick()
  {
    if (this->_checked)
      this->_checked = false;
    else
      this->_checked = true;
    return (true);
  }

  bool		ToggleButton::initialize()
  {
    for (size_t i = 0; i < this->_label.size(); i++)
      {
	Letter* l = new Letter(this->_label[i], this->_color);
	if (!l->initialize())
	  {
	    std::cerr << "Error while initializing letter " << this->_label[i];
	    std::cerr << std::endl;
	    return (false);
	  }
	this->_letters.push_back(l);
      }

    Letter* l = new Letter(' ', this->_color);
    if (!l->initialize())
      return (false);
    this->_letters.push_back(l);

    l = new Letter('o', this->_color);
    if (!l->initialize())
      return (false);
    this->_on.push_back(l);

    l = new Letter('o', this->_color);
    if (!l->initialize())
      return (false);
    this->_off.push_back(l);

    l = new Letter('n', this->_color);
    if (!l->initialize())
      return (false);
    this->_on.push_back(l);

    l = new Letter('f', this->_color);
    if (!l->initialize())
      return (false);
    this->_off.push_back(l);

    l = new Letter('f', this->_color);
    if (!l->initialize())
      return (false);
    this->_off.push_back(l);

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
    size_t j = i;
    for (std::list<Letter*>::iterator it = this->_on.begin();
	 it != this->_on.end(); it++)
      {
	(*it)->translate(glm::vec3(0, 0,
				   static_cast<float>(6 -
						      static_cast<float>(j)/2)));
	j++;
      }
    j = i;
    for (std::list<Letter*>::iterator it = this->_off.begin();
	 it != this->_off.end(); it++)
      {
	(*it)->translate(glm::vec3(0, 0,
				   static_cast<float>(6 -
						      static_cast<float>(j)/2)));
	j++;
      }
    return (true);
  }

  void		ToggleButton::draw(ARenderer& r, const RenderState& s)
  {
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end(); it++)
      (*it)->draw(r, s);
    if (this->_checked)
      for (std::list<Letter*>::iterator it = this->_on.begin();
	   it != this->_on.end(); it++)
	(*it)->draw(r, s);
    else
      for (std::list<Letter*>::iterator it = this->_off.begin();
	   it != this->_off.end(); it++)
	(*it)->draw(r, s);
  }

  void		ToggleButton::translateButton(const glm::vec3& pos)
  {
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end(); it++)
      (*it)->translate(pos);
    for (std::list<Letter*>::iterator it = this->_on.begin();
	 it != this->_on.end(); it++)
      (*it)->translate(pos);
    for (std::list<Letter*>::iterator it = this->_off.begin();
	 it != this->_off.end(); it++)
      (*it)->translate(pos);
  }

  void		ToggleButton::setChecked(bool checked)
  {
    this->_checked = checked;
  }

  bool		ToggleButton::isChecked() const
  {
    return (this->_checked);
  }

  ToggleButton::~ToggleButton()
  {
  }

}
