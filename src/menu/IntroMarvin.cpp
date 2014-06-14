#include		"IntroMarvin.hh"

namespace		bbm
{

  IntroMarvin::IntroMarvin() :
    Model("introbomberman", "default", 0.0015)
  {
    this->_model->setCurrentAnim(0);
    this->_model->createSubAnim(0, "salto", 0, 64);
    this->_model->setCurrentSubAnim("salto", false);
  }

  IntroMarvin::~IntroMarvin()
  {
  }

}
