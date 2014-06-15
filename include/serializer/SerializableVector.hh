//
// SerializableVector.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:22:49 2014 Manu
// Last update Sun Jun 15 13:22:49 2014 Manu
//

#ifndef SERIALIZABLE_VECTOR_HH
# define SERIALIZABLE_VECTOR_HH

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "serializer/ISerializable.hh"
#include "serializer/ISerializedNode.hh"

template<typename ValueType>
class SerializableVector : public ISerializable, public std::vector<ValueType>
{
public:
  SerializableVector();
  ~SerializableVector();

  void	pack(ISerializedNode & current) const;
  void	unpack(const ISerializedNode & current);
};

#include "serializer/SerializableVector.tpp"

#endif
