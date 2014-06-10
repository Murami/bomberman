//
// AModel.cpp for bomberman in /home/manu/tek2/CPP/bomberman/model_and_animation
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue May 27 16:41:06 2014 Manu
// Last update Sat Jun  7 15:59:55 2014 Manu
//

#include		"ModelManager.hpp"
#include		"AModel.hh"

namespace		bbm
{

  AModel::AModel(const std::string& filename) : AObject(), _filename(filename)
  {
    this->_direction = FRONT;
    this->_keyup = false;
    this->_keydown = false;
    this->_keyleft = false;
    this->_keyright = false;
    this->_speed = 0.25f;
    this->_shader = ShaderManager::getInstance()->getShader("default");
  }

  void		AModel::setDirection(AModel::Direction)
  {
  }

  AModel::Direction	AModel::getDirection() const
  {
    return (this->_direction);
  }

  bool		AModel::initialize()
  {
    this->_model = ModelManager::getInstance()->getModel("selector");
    this->_createAnimations();
    this->_running = false;
    return (true);
  }

  void		AModel::pause()
  {
    this->_model->pause(true);
  }

  void		AModel::play()
  {
    this->_model->pause(false);
  }

  void		AModel::setCurrentAnimation(const std::string& animName, bool l)
  {
    this->_model->setCurrentSubAnim(animName, l);
  }

  void		AModel::draw(ARenderer&, const RenderState& state)
  {
    RenderState s(state);
    s.transform = state.transform * this->getTransformation();
    // glAlphaFunc(GL_GREATER, 0.1f);
    //r.draw(this->_model, NULL, this->_shader, s, GL_QUADS);
    //this->_model->draw(*this->_shader, this->getTransformation(), 0.1f);
  }

  // void		AModel::draw(gdl::AShader& shader, const gdl::Clock& clock)
  // {
  //   this->_model.draw(shader, this->getTransformation(), clock.getElapsed());
  // }

  AModel::~AModel()
  {
  }

}
