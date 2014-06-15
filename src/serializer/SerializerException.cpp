//
// SerializerException.cpp for bomberman in /home/manu/rendu/cpp_bomberman/src/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:20:49 2014 Manu
// Last update Sun Jun 15 13:20:49 2014 Manu
//

#include "serializer/SerializerException.hh"

SerializerException::SerializerException(const std::string& what) throw() : runtime_error(what)
{
}
