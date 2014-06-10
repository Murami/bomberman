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
