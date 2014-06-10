#include "serializer/SerializerException.hh"

SerializerException::SerializerException(const std::string& what) throw() : runtime_error(what)
{
}
