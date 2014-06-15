//
// SerializableMap.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:22:52 2014 Manu
// Last update Sun Jun 15 13:22:52 2014 Manu
//

#ifndef SERIALIZABLE_MAP_HH
# define SERIALIZABLE_MAP_HH

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "serializer/ISerializable.hh"
#include "serializer/ISerializedNode.hh"

template<typename FirstType, typename SecondType>
class SerializablePair : public ISerializable,
			 public std::pair<FirstType, SecondType>
{
public:
  SerializablePair();
  SerializablePair(const std::pair<FirstType, SecondType> pair);
  ~SerializablePair();

  SerializablePair& operator=(const std::pair<FirstType, SecondType> pair);

  void	pack(ISerializedNode & current) const;
  void	unpack(const ISerializedNode & current);
};

template<typename IndexType, typename ValueType>
class SerializableMap : public ISerializable,
			public std::map<IndexType, ValueType>
{
public:
  SerializableMap();
  ~SerializableMap();

  void	pack(ISerializedNode & current) const;
  void	unpack(const ISerializedNode & current);
};

#include "serializer/SerializableMap.tpp"

#endif
