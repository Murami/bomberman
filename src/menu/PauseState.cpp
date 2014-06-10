#include		"game/GameManager.hh"
#include		"PauseState.hh"

namespace		bbm
{
  PauseState::PauseState(GameManager& manager) : _manager(manager)
  {
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
  }

  void		PauseState::initialize()
  {
  }

  void		PauseState::release()
  {
  }

  void		PauseState::obscuring()
  {
  }

  void		PauseState::update(float time, const Input& input)
  {
    if (input.getKeyDown(SDLK_ESCAPE) || input.getEvent(SDL_QUIT))
      {
	_manager.pop();
      }
  }

  void		PauseState::draw(float time, Screen& context)
  {
  }

  void		PauseState::revealing()
  {
  }

  void		PauseState::setPlayMenu()
  {
  }

  void		PauseState::setOptionsMenu()
  {
  }

  void		PauseState::setHighScoreMenu()
  {
  }

  void		PauseState::exitGame()
  {
  }

  void		PauseState::setNewGameMenu()
  {
  }

  void		PauseState::setContinueGameMenu()
  {
  }

  void		PauseState::setLoadGameMenu()
  {
  }

  void		PauseState::setMainMenu()
  {
  }

  void		PauseState::setOptionsAudioMenu()
  {
  }

  void		PauseState::setOptionsControlMenu()
  {
  }

  void		PauseState::setNextFrame()
  {
  }

  void		PauseState::setPrevFrame()
  {
  }

  void		PauseState::setIASelection1Menu()
  {
  }

  void		PauseState::setIASelection2Menu()
  {
  }

  void		PauseState::setIASelection3Menu()
  {
  }

  void		PauseState::setIASelection4Menu()
  {
  }

  void		PauseState::launchNewGame()
  {
  }

  void		PauseState::setOptionControlPlayer1()
  {
  }

  void		PauseState::setOptionControlPlayer2()
  {
  }

  void		PauseState::setMapParamsMenu()
  {
  }

  PauseState::~PauseState()
  {
  }
}
