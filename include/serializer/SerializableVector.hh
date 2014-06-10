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
