#ifndef SERIALIZABLE_LIST_HH
# define SERIALIZABLE_LIST_HH

#include <list>
#include <iostream>
#include <sstream>
#include "serializer/ISerializable.hh"
#include "serializer/ISerializedNode.hh"

template<typename ValueType>
class SerializableList : public ISerializable, public std::list<ValueType>
{
public:
  SerializableList();
  ~SerializableList();

  void	pack(ISerializedNode & current) const;
  void	unpack(const ISerializedNode & current);
};

#include "serializer/SerializableList.tpp"

#endif
