//
// GameOverState.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:28:40 2014 otoshigami
// Last update Sun Jun 15 11:03:41 2014 Manu
//

#include <sstream>
#include <string>
#include "game/GameOverState.hh"
#include "game/GameManager.hh"
#include "game/GameState.hh"
#include "game/HighScore.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/ModelManager.hh"
#include "graphic/Object.hh"
#include "graphic/Camera.hh"
#include "graphic/RenderState.hh"
#include "graphic/ProjectionPerspective.hh"
#include "graphic/Screen.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"
#include "sound/SoundManager.hh"
#include "events/Input.hh"
#include "MenuState.hh"
#include "menu/Letter.hh"

const float scaleFactor = 1.0;

namespace bbm
{
  GameOverState::GameOverState(GameManager& gameManager, const std::string & type, int score) :
    _manager(gameManager), _type(type)
  {
    _score = score;
    glDisable(GL_CULL_FACE);
    for (size_t i = 0; i < type.size(); i++)
      {
	Letter* l = new Letter(type[i], glm::vec4(1, 1, 1, 1));
	l->initialize();
	this->_typeLetters.push_back(l);
      }
    std::string str("press space");
    for (size_t i = 0; i < str.size(); i++)
      {
	Letter* l = new Letter(str[i], glm::vec4(1, 1, 1, 1));
	l->initialize();
	this->_pressSpace.push_back(l);
      }
    str = std::string("your score : ");
    std::stringstream ss;
    ss << score;
    str += ss.str();
    for (size_t i = 0; i < str.size(); i++)
      {
	Letter* l = new Letter(str[i], glm::vec4(1, 1, 1, 1));
	l->initialize();
	this->_playerScore.push_back(l);
      }
    this->_getNewHighScore = false;
    HighScore highscore;
    highscore.load("HighScores");
    std::vector<int> scores = highscore.getScores();
    for (size_t i = 0; i < scores.size(); i++)
      {
	if (score >= scores[i])
	  {
	    this->_getNewHighScore = true;
	    break;
	  }
      }
    this->_updated = false;
  }

  GameOverState::~GameOverState()
  {
  }

  void			GameOverState::saveHighScore()
  {
    HighScore		highScores;

    highScores.load("HighScores");
    highScores.addScore(_score);
    highScores.save("HighScores");
  }

  void			GameOverState::initialize()
  {
  }

  void			GameOverState::release()
  {
  }

  void			GameOverState::obscuring()
  {
  }

  void			GameOverState::update(float time, const Input& input)
  {
    (void)time;
    if (!this->_updated)
      {
	int i = 0;
	for (std::list<Letter*>::iterator it = this->_typeLetters.begin();
	     it != this->_typeLetters.end(); it++)
	  {
	    (*it)->translate(glm::vec3(0, 3, (static_cast<float>(this->_typeLetters.size()) / 4) - (static_cast<float>(i) / 2)));
	    i++;
	  }
	i = 0;
	for (std::list<Letter*>::iterator it = this->_pressSpace.begin();
	     it != this->_pressSpace.end(); it++)
	  {
	    (*it)->translate(glm::vec3(0, -4, (static_cast<float>(this->_pressSpace.size()) / 4) - (static_cast<float>(i) / 2)));
	    i++;
	  }
	i = 0;
	for (std::list<Letter*>::iterator it = this->_playerScore.begin();
	     it != this->_playerScore.end(); it++)
	  {
	    (*it)->scale(glm::vec3(1, 1.25f, 1.25f));
	    (*it)->translate(glm::vec3(0, 0, (static_cast<float>(this->_playerScore.size()) / 3) - (static_cast<float>(i) / 2)));
	    i++;
	  }
	this->_updated = true;
      }
    if (input.getKeyDown(SDLK_SPACE))
      {
	saveHighScore();
	_manager.pop();
      }
  }

  void			GameOverState::draw(float time, Screen& context)
  {
    (void) time;
    Transform		cam = Camera(glm::vec3(10, 0, 0), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    Transform		projection = ProjectionPerspective(60, context.getSize().x / context.getSize().y, 0.1f, 1000);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();
    for (std::list<Letter*>::iterator it = this->_typeLetters.begin();
	 it != this->_typeLetters.end(); it++)
      (*it)->draw(context, RenderState(projection, cam));
    for (std::list<Letter*>::iterator it = this->_pressSpace.begin();
	 it != this->_pressSpace.end(); it++)
      (*it)->draw(context, RenderState(projection, cam));
    for (std::list<Letter*>::iterator it = this->_playerScore.begin();
	 it != this->_playerScore.end(); it++)
      (*it)->draw(context, RenderState(projection, cam));
    context.flush();
  }

  void			GameOverState::revealing()
  {
    _manager.pop();
  }
};
