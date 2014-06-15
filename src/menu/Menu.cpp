//
// Menu.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_5
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Fri May 30 10:53:03 2014 Manu
// Last update Sun Jun 15 12:09:56 2014 Manu
//

#include		"sound/SoundManager.hh"
#include		"FileExplorer.hh"
#include		"Frame.hh"
#include		"graphic/ModelManager.hh"
#include		"Menu.hh"
#include		"game/HighScore.hh"

namespace	bbm
{

  Menu::Menu(const std::string& title, IMenuManager* manager) :
    _title(title), _manager(manager)
  {
    this->_frame = NULL;
  }

  const std::list<AButton*>&	Menu::getButtons() const
  {
    return (this->_buttons);
  }

  FileExplorer*	Menu::getExplorer()
  {
    return (this->_frame->getExplorer());
  }

  bool		Menu::initialize()
  {
    ModelManager::getInstance()->addModel("arrow", "./assets/menu/models/arrow.obj");
    this->_selected = 0;
    this->_selector = new Selector();
    this->_selector->setRoll(90.0f);
    this->_selector->setYaw(-90.0f);
    this->_selector->setScale(glm::vec3(0.5f, 0.75f, 0.75f));
    this->_selector->move(glm::vec3(0, 0, 7.0f));
    if (this->_buttons.size())
      this->_selector->move(glm::vec3(0, -(this->_strings.size() / 2) + (static_cast<float>(this->_buttons.
							     size()) / 2), 0));
    return (true);
  }

  void		Menu::refresh()
  {
    static bool	ref = false;
    ToggleButton* sound = dynamic_cast<ToggleButton*>(*(this->_buttons.begin()));
    if (sound)
      sound->setChecked(SoundManager::getInstance()->soundPlaying());
    if ((*(this->_buttons.begin()))->getLabel() == "sound" ||
	(*(this->_buttons.begin()))->getLabel() == "music")
      {
	ToggleButton* music = dynamic_cast<ToggleButton*>((*(this->_buttons.begin()) + 1));
	if (music)
	  music->setChecked(SoundManager::getInstance()->musicPlaying());
      }
    if (this->_frame)
      {
	delete (this->_frame);
	this->_frame = new Frame(glm::vec4(0.5f, 0.5f, 0.5f, 1));
	this->_frame->scale(glm::vec3(1.0f, 10.0f, 13.5f));
	this->_frame->translate(glm::vec3(0, -5, -10));
	this->_frame->initialize();
      }
    if (this->_title == "highscores")
      {
	this->_strings.empty();
	this->_strings.clear();
	HighScore hs;
	hs.load("HighScores");
	for (std::vector<int>::const_iterator it = hs.getScores().begin();
	     it != hs.getScores().end(); it++)
	  {
	    std::stringstream ss;
	    ss << *it;
	    this->createNewString(ss.str());
	  }
	size_t k = this->_buttons.size();
	for (size_t i = 0; i < this->_strings.size(); i++)
	  {
	    for (size_t j = 0; j < this->_strings[i].size(); j++)
	      {
		this->_strings[i][j]->translate(glm::vec3(0, -(this->_strings.size() / 2) + (static_cast<float>(this->_buttons.size()) / 2) +
							  k, 6 - static_cast<float>(j) / 2));
	      }
	    k++;
	  }
	if (!ref)
	  {
	    this->_selector->move(glm::vec3(0, -(this->_strings.size() / 2) + (static_cast<float>(this->_buttons.size()) / 2), 0));
	    (*(this->_buttons.begin()))->translateButton(glm::vec3(0, -(this->_strings.size() / 2) + (static_cast<float>(this->_buttons.size()) / 2) - 0.5f, 0));
	    ref = true;
	  }
      }
  }

  void		Menu::finalize()
  {
    int		i = 0;
    int		size = this->_buttons.size();
    this->_selector->move(glm::vec3(0, -this->_strings.size() + (static_cast<float>(size) / 2), 0));
    for (std::list<AButton*>::iterator it = this->_buttons.begin();
	 it != this->_buttons.end(); it++)
      {
	(*it)->translateButton(glm::vec3(0, -(this->_strings.size()/2) + (static_cast<float>(size) / 2) -
					 i, 0));
	i++;
      }
    size_t k = i;
    for (size_t i = 0; i < this->_strings.size(); i++)
      {
	for (size_t j = 0; j < this->_strings[i].size(); j++)
	  {
	    this->_strings[i][j]->translate(glm::vec3(0, -(this->_strings.size() / 2) + (static_cast<float>(size) / 2) +
						      k, 6 - static_cast<float>(j) / 2));
	  }
	k++;
      }
  }

  void		Menu::_handleKeyDown(const Input& input)
  {
    if (input.getKeyDown(SDLK_DOWN))
      {
	this->_selected++;
	this->_selector->move(glm::vec3(0, -1, 0));
	if (this->_selected == static_cast<int>(this->_buttons.size()))
	  {
	    this->_selector->move(glm::vec3(0, this->_selected, 0));
	    this->_selected = 0;
	  }
      }
  }

  void		Menu::_handleKeyUp(const Input& input)
  {
    if (input.getKeyDown(SDLK_UP))
      {
	this->_selected--;
	this->_selector->move(glm::vec3(0, 1, 0));
	if (this->_selected < 0)
	  {
	    this->_selector->move(glm::vec3(0, -static_cast<float>(this->_buttons.size()), 0));
	    this->_selected = this->_buttons.size() - 1;
	  }
      }
  }

  void		Menu::_handleKeyReturn(const Input& input)
  {
    if (input.getKeyDown(SDLK_RETURN))
      {
	std::list<void (IMenuManager::*)(Menu*)>::iterator it;
	it = this->_callbacks.begin();
	for (int i = 0; i < this->_selected; i++)
	  it++;
	std::list<AButton*>::iterator b = this->_buttons.begin();
	for (int i = 0; i < this->_selected; i++)
	  b++;
	if (!(*b)->onClick())
	  {
	    if ((*b)->useCallback())
	      this->_selector->move(glm::vec3(0, -(static_cast<float>(this->_buttons.size()) / 2), 0));
	    (this->_manager->*(*it))(this);
	  }
      }
  }

  void		Menu::_handleKeyRight(const Input& input)
  {
    if (input.getKeyDown(SDLK_RIGHT))
      {
	std::list<AButton*>::iterator it = this->_buttons.begin();
	for (int i = 0; i < this->_selected; i++)
	  it++;
	if ((*it)->getType() == "state")
	  (*it)->nextState();
      }
  }

  void		Menu::_handleKeyLeft(const Input& input)
  {
    if (input.getKeyDown(SDLK_LEFT))
      {
	std::list<AButton*>::iterator it = this->_buttons.begin();
	for (int i = 0; i < this->_selected; i++)
	  it++;
	if ((*it)->getType() == "state")
	  (*it)->prevState();
      }
  }

  void		Menu::update(const Input& input)
  {
    this->_handleKeyDown(input);
    this->_handleKeyUp(input);
    this->_handleKeyLeft(input);
    this->_handleKeyRight(input);
    this->_handleKeyReturn(input);
    this->_selector->pitch(1.0f);
  }

  void		Menu::createNewString(const std::string& str)
  {
    std::vector<Letter*> v;
    for (size_t i = 0; i < str.size(); i++)
      {
	Letter* l = new Letter(str[i], glm::vec4(1, 1, 1, 1));
	l->initialize();
	v.push_back(l);
      }
    this->_strings.push_back(v);
  }

  void		Menu::createNewStateButton(const std::string& label,
					   void (IMenuManager::*func)(Menu*),
					   size_t spaces,
					   const glm::vec4& color,
					   const std::string& defaultState)
  {
    AButton* button = new StateButton(label, spaces, defaultState, color);
    button->initialize();
    this->_buttons.push_back(button);
    this->_callbacks.push_back(func);
  }

  void		Menu::createNewButton(const std::string& label,
				      void (IMenuManager::*fPtr)(Menu*),
				      const glm::vec4& color,
				      bool clickable)
  {
    AButton* button = new Button(label, color, clickable);
    button->initialize();
    this->_buttons.push_back(button);
    this->_callbacks.push_back(fPtr);
  }

  void		Menu::createNewToggleButton(const std::string& label,
					    void (IMenuManager::*fPtr)(Menu*),
					    const glm::vec4& color, bool state)
  {
    AButton* button = new ToggleButton(label, color, state);
    button->initialize();
    this->_buttons.push_back(button);
    this->_callbacks.push_back(fPtr);
  }

  void		Menu::createFrame()
  {
    this->_frame = new Frame(glm::vec4(0.5f, 0.5f, 0.5f, 1));
    this->_frame->scale(glm::vec3(1.0f, 10.0f, 13.5f));
    this->_frame->translate(glm::vec3(0, -5, -10));
    this->_frame->initialize();
  }

  void		Menu::draw(ARenderer& r, const RenderState& s)
  {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    for (std::list<AButton*>::iterator it = this->_buttons.begin();
	 it != this->_buttons.end(); it++)
      (*it)->draw(r, s);
    glEnable(GL_DEPTH_TEST);
    glAlphaFunc(GL_GREATER, 0.25f);
    r.draw(*this->_selector, s);
    for (size_t i = 0; i < this->_strings.size(); i++)
      for (size_t j = 0; j < this->_strings[i].size(); j++)
	this->_strings[i][j]->draw(r, s);
    if (this->_frame != NULL)
      {
	this->_frame->draw(r, s);
      }
    glEnable(GL_CULL_FACE);
  }

  void		Menu::removeStateFromLastButton(const std::string& state)
  {
    std::list<AButton*>::iterator it = this->_buttons.begin();
    while (it != this->_buttons.end())
      it++;
    it--;
    StateButton* s = reinterpret_cast<StateButton*>(*it);
    s->removeState(state);
  }

  void		Menu::addStateToLastButton(const std::string& state)
  {
    std::list<AButton*>::iterator it;
    for (it = this->_buttons.begin();
	 it != this->_buttons.end(); it++);
    it--;
    StateButton* s = reinterpret_cast<StateButton*>(*it);
    s->addState(state);
  }

  void		Menu::setNextFrame()
  {
    this->_frame->nextSave();
  }

  void		Menu::setPrevFrame()
  {
    this->_frame->prevSave();
  }

  const std::string&	Menu::getTitle() const
  {
    return (this->_title);
  }

  Menu::~Menu()
  {
    delete (this->_selector);
    delete (this->_frame);
    for (std::list<AButton*>::iterator it = this->_buttons.begin();
	 it != this->_buttons.end(); it++)
      delete (*it);
  }
}
