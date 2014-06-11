//
// StateButton.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 17:43:53 2014 Manu
// Last update Wed Jun 11 03:41:32 2014 Manu
//

#include		"Letter.hh"
#include		"StateButton.hh"

namespace		bbm
{

  StateButton::StateButton(const std::string& label,
			   size_t nbSpaces,
			   const std::string& defaultState,
			   const glm::vec4& color) :
    AButton(label, color, true, "state")
  {
    this->_nbSpaces = nbSpaces;
    this->_states.push_back(defaultState);
    this->_currentState = this->_states[0];
    this->_index = 0;
  }

  void			StateButton::removeState(const std::string& state)
  {
    for (size_t i = 0; i < this->_states.size(); i++)
      {
	if (this->_states[i] == state)
	  {
	    this->_states.erase(this->_states.begin() + i);
	    this->_stateLetters.erase(this->_stateLetters.begin() + i);
	    break;
	  }
      }
  }

  bool			StateButton::initialize()
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
    for (size_t i = 0; i < this->_nbSpaces; i++)
      {
	Letter* l = new Letter(' ', this->_color);
	if (!l->initialize())
	  return (false);
	this->_letters.push_back(l);
      }
    this->_stateLetters.push_back(std::vector<Letter*>());
    for (size_t i = 0; i < this->_states[0].size(); i++)
      {
	Letter* l = new Letter(this->_states[0][i], this->_color);
	if (!l->initialize())
	  return (false);
	this->_stateLetters[0].push_back(l);
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
    size_t j = i;
    size_t k = 0;
    while (k < this->_stateLetters[0].size())
      {
	this->_stateLetters[0][k]->translate(glm::vec3(0, 0, static_cast<float>(6 - static_cast<float>(j)/2)));
	j++;
	k++;
	i++;
      }
    return (true);
  }

  void			StateButton::draw(ARenderer& r, const RenderState& s)
  {
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end(); it++)
      (*it)->draw(r, s);
    for (size_t i = 0; i < this->_stateLetters[this->_index].size(); i++)
      this->_stateLetters[this->_index][i]->draw(r, s);
  }

  void			StateButton::translateButton(const glm::vec3& pos)
  {
    for (std::list<Letter*>::iterator it = this->_letters.begin();
	 it != this->_letters.end(); it++)
      (*it)->translate(pos);
    for (size_t i = 0; i < this->_stateLetters.size(); i++)
      for (size_t j = 0; j < this->_stateLetters[i].size(); j++)
	this->_stateLetters[i][j]->translate(pos);
  }

  void			StateButton::nextState()
  {
    this->_index++;
    if (this->_index == this->_states.size())
      this->_index = 0;
    this->_currentState = this->_states[this->_index];
  }

  void			StateButton::prevState()
  {
    this->_index--;
    int i = static_cast<int>(this->_index);
    if (i < 0)
      this->_index = this->_states.size() - 1;
    this->_currentState = this->_states[this->_index];
  }

  bool			StateButton::onClick()
  {
    this->_index++;
    if (this->_index == this->_states.size())
      this->_index = 0;
    this->_currentState = this->_states[this->_index];
    return (true);
  }

  const std::string&	StateButton::getState()
  {
    return (this->_currentState);
  }

  void			StateButton::addState(const std::string& state)
  {
    this->_states.push_back(state);
    this->_stateLetters.push_back(std::vector<Letter*>());
    for (size_t i = 0; i < this->_states[this->_states.size() - 1].size(); i++)
      {
    	Letter* l = new Letter(this->_states[this->_states.size() - 1][i], this->_color);
    	l->initialize();
    	this->_stateLetters[this->_stateLetters.size() - 1].push_back(l);
      }
    size_t j = this->_letters.size();
    size_t k = 0;
    while (k < this->_stateLetters[this->_stateLetters.size() - 1].size())
      {
    	this->_stateLetters[this->_stateLetters.size() - 1][k]->translate(glm::vec3(0, 0, static_cast<float>(6 - static_cast<float>(j+k)/2)));
    	k++;
      }
  }

  StateButton::~StateButton()
  {
  }

}
