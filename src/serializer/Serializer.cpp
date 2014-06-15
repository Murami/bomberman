//
// Serializer.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:20:52 2014 Manu
// Last update Sun Jun 15 13:20:53 2014 Manu
//

#include "serializer/Serializer.hh"

Serializer::Serializer(ISerializer* serializer)
{
  _serializer = serializer;
}

Serializer::~Serializer()
{
}

ISerializer*	Serializer::operator->()
{
  return (_serializer);
}
