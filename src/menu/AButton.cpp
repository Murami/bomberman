//
// AButton.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 11:51:07 2014 Manu
// Last update Mon Jun  9 17:51:02 2014 Manu
//

#include		"AButton.hh"

namespace		bbm
{

  AButton::AButton(const std::string& label, const glm::vec4& color, bool b,
		   const std::string& type) :
    AObject(), _label(label), _color(color), _useCallback(b)
  {
    this->_type = type;
    this->_selectable = true;
  }

  void			AButton::setSelectable(bool b)
  {
    this->_selectable = b;
  }

  bool			AButton::isSelectable() const
  {
    return (this->_selectable);
  }

  bool			AButton::useCallback() const
  {
    return (this->_useCallback);
  }

  const std::string&	AButton::getType() const
  {
    return (this->_type);
  }

  size_t		AButton::getSize() const
  {
    return (this->_letters.size());
  }

  const std::string&	AButton::getLabel() const
  {
    return (this->_label);
  }

  AButton::~AButton()
  {
  }

}
