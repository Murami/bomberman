//
// GameOverState.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:28:40 2014 otoshigami
// Last update Sun Jun 15 08:28:41 2014 otoshigami
//

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

const float scaleFactor = 1.0;

namespace bbm
{
  GameOverState::GameOverState(GameManager& gameManager, const std::string & type, int score) :
    _manager(gameManager)
  {
    _score = score;
    glDisable(GL_CULL_FACE);
    _screenOver = new Object(type, "default", GL_QUADS);
    _screenOver->pushVertex(glm::vec3(-0.5, -0.5, 0));
    _screenOver->pushVertex(glm::vec3(-0.5, 0.5, 0));
    _screenOver->pushVertex(glm::vec3(0.5, 0.5, 0));
    _screenOver->pushVertex(glm::vec3(0.5, -0.5, 0));
    _screenOver->pushUv(glm::vec2(0, 0));
    _screenOver->pushUv(glm::vec2(0, 1));
    _screenOver->pushUv(glm::vec2(1, 1));
    _screenOver->pushUv(glm::vec2(1, 0));
    _screenOver->build();
    _screenOver->scale(glm::vec3(scaleFactor, scaleFactor, 0));
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
    delete (_screenOver);
  }

  void			GameOverState::obscuring()
  {
  }

  void			GameOverState::update(float time, const Input& input)
  {
    (void)time;
    if (input.getKeyDown(SDLK_SPACE))
      {
	saveHighScore();
	_manager.pop();
      }
  }

  void			GameOverState::draw(float time, Screen& context)
  {
    (void) time;
    Transform		cam = Camera(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    Transform		projection = ProjectionPerspective(60, 1600 / 900, 1, 1000);

    context.split(glm::ivec2(0, 0), glm::ivec2(context.getSize().x, context.getSize().y));
    context.clear();
    context.draw(*_screenOver, RenderState(projection, cam));
    context.flush();
  }

  void			GameOverState::revealing()
  {
    _manager.pop();
  }
};
