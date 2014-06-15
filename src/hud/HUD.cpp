#include		"menu/LetterManager.hpp"
#include		"menu/Letter.hh"
#include		"graphic/Transform.hh"
#include		"graphic/Camera.hh"
#include		"menu/Image.hh"
#include		"graphic/ARenderer.hh"
#include		"graphic/RenderState.hh"
#include		"hud/HUD.hh"

namespace		bbm
{
  const std::string	HUD::NORMAL_BOMB_PATH = "./assets/hud/NormalBomb.tga";
  const std::string	HUD::WATER_BOMB_PATH = "./assets/hud/AquaBomb.tga";
  const std::string	HUD::DARK_BOMB_PATH = "./assets/hud/DarkBomb.tga";
  const std::string	HUD::POWER_BOMB_PATH = "./assets/hud/PowerBomb.tga";
  const std::string	HUD::MULTI_BOMB_PATH = "./assets/hud/WindBomb.tga";
  const std::string	HUD::BOX_BOMB_PATH = "./assets/hud/BlockBomb.tga";
  const std::string	HUD::BACKGROUND_PATH = "./assets/hud/background.tga";
  const std::string	HUD::RANDOM_BOMB_PATH = "./assets/hud/RandomBomb.tga";
  const std::string	HUD::DARK_MALUS_PATH = "./assets/hud/dark_bonus.tga";
  const std::string	HUD::SLOW_MALUS_PATH = "./assets/hud/water_bonus.tga";

  HUD::HUD()
  {
  }

  void			HUD::initialize()
  {
    this->_normalBomb = new Image(NORMAL_BOMB_PATH);
    this->_normalBomb->initialize();
    this->_normalBomb->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_background = new Image(BACKGROUND_PATH);
    this->_background->initialize();
    this->_background->translate(glm::vec3(8.5f, 0.15f, 0));
    this->_bonusBombs[DARK] = new Image(DARK_BOMB_PATH);
    this->_bonusBombs[RANDOM] = new Image(RANDOM_BOMB_PATH);
    this->_bonusBombs[POWER] = new Image(POWER_BOMB_PATH);
    this->_bonusBombs[WATER] = new Image(WATER_BOMB_PATH);
    this->_bonusBombs[BOX] = new Image(BOX_BOMB_PATH);
    this->_bonusBombs[MULTI] = new Image(MULTI_BOMB_PATH);
    this->_bonusBombs[DARK]->initialize();
    this->_bonusBombs[RANDOM]->initialize();
    this->_bonusBombs[POWER]->initialize();
    this->_bonusBombs[WATER]->initialize();
    this->_bonusBombs[MULTI]->initialize();
    this->_bonusBombs[BOX]->initialize();
    this->_bonusBombs[DARK]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[RANDOM]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[POWER]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[WATER]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[MULTI]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[BOX]->translate(glm::vec3(0, 5.375f, 4));
    this->_bonusBombs[DARK]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_bonusBombs[RANDOM]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_bonusBombs[POWER]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_bonusBombs[WATER]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_bonusBombs[MULTI]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_bonusBombs[BOX]->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_dark = new Image(DARK_MALUS_PATH);
    this->_slow = new Image(SLOW_MALUS_PATH);
    this->_dark->initialize();
    this->_dark->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_dark->scale(glm::vec3(1, 0.5f, 0.5f));
    this->_dark->translate(glm::vec3(0, 5.25f, 4.5f));
    this->_slow->initialize();
    this->_slow->scale(glm::vec3(1, 0.5f, 0.25f));
    this->_slow->scale(glm::vec3(1, 0.5f, 0.5f));
    this->_slow->translate(glm::vec3(0, 5.25f, 4.75f));
  }

  void			HUD::_createScore(const std::string& score)
  {
    this->_list.empty();
    this->_list.clear();
    for (size_t i = 0; i < score.size(); i++)
      {
	Letter* l = new Letter(score[i], glm::vec4(1, 1, 1, 1));
	l->initialize();
	this->_list.push_back(l);
      }
    int i = 0;
    for (std::list<Letter*>::iterator it = this->_list.begin();
	 it != this->_list.end(); it++)
      {
	(*it)->translate(glm::vec3(0, 5.25f, 3-static_cast<float>(i)/2));
	i++;
      }
  }

  void			HUD::draw(ARenderer & renderer,
				  const RenderState &)
  {
    Transform		perspective = ProjectionPerspective(60, 1920 / 1080, 0.1f, 1000);
    Transform		camera = Camera(glm::vec3(10, 0, 0),
					glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    RenderState		state(perspective, camera);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    this->_background->draw(renderer, state);
    for (int i = 0; i < this->_nbBombs; i++)
      {
	this->_normalBomb->setPosition(glm::vec3(0, 5.25f, -4 + static_cast<float>(i) / 4));
	this->_normalBomb->draw(renderer, state);
      }
    if (this->_bonus == DARK ||
	this->_bonus == POWER ||
	this->_bonus == BOX ||
	this->_bonus == MULTI ||
	this->_bonus == RANDOM ||
	this->_bonus == WATER)
      this->_bonusBombs[this->_bonus]->draw(renderer, state);
    std::list<Letter*> list;
    std::stringstream ss;
    ss << this->_score;
    this->_createScore(ss.str());
    for (std::list<Letter*>::iterator it = this->_list.begin();
	 it != this->_list.end(); it++)
      (*it)->draw(renderer, state);
    if (this->_darkMalus)
      this->_dark->draw(renderer, state);
    if (this->_slowMalus)
      this->_slow->draw(renderer, state);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
  }

  void			HUD::update(APlayer* player)
  {
    this->_score = player->getScore();
    this->_bonus = player->getBonusType();
    this->_darkMalus = player->isDark();
    this->_slowMalus = player->isSlow();
    this->_nbBombs = player->getBomb();
  }

  void			HUD::setType(BombType type)
  {
    this->_bonus = type;
  }

  void			HUD::setNbBombs(int nb)
  {
    this->_nbBombs = nb;
  }

  void			HUD::setScore(int score)
  {
    this->_score = score;
  }

  void			HUD::setDark(bool dark)
  {
    this->_darkMalus = dark;
  }

  void			HUD::setSlow(bool slow)
  {
    this->_slowMalus = slow;
  }

  BombType		HUD::getType() const
  {
    return (this->_bonus);
  }

  int			HUD::getNbBombs() const
  {
    return (this->_nbBombs);
  }

  int			HUD::getScore() const
  {
    return (this->_score);
  }

  bool			HUD::hasDarkMalus() const
  {
    return (this->_darkMalus);
  }

  bool			HUD::hasSlowMalus() const
  {
    return (this->_slowMalus);
  }

  HUD::~HUD()
  {
  }
}
