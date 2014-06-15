//
// Serializer.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:22:42 2014 Manu
// Last update Sun Jun 15 13:22:42 2014 Manu
//

#ifndef SERIALIZER_HH
# define SERIALIZER_HH

# include <memory>
# include <iostream>
# include <map>
class	ISerializer;
class	ISerializedNode;

class	Serializer
{

public:
  Serializer(ISerializer* serializer);
  ~Serializer();

  template<typename T>
  static Serializer	create();

  ISerializer*	operator->();

private:
  ISerializer*	_serializer;
};

#include "serializer/Serializer.tpp"

#endif /* SERIALIZER_HH */
