//
// IntroMarvin.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/menu
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 11:48:36 2014 Manu
// Last update Sun Jun 15 11:48:37 2014 Manu
//

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
