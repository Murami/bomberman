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
