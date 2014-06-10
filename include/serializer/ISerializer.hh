#ifndef ISERIALIZER_HH
#define ISERIALIZER_HH

#include <string>
#include <fstream>

class	ISerializable;

class	ISerializer
{
public:
  virtual ~ISerializer() {}

  virtual void	serializeToFile(const std::string& filename, ISerializable & obj) const = 0;
  virtual void	serializeToString(const std::string& buffer, ISerializable & obj) const = 0;

  virtual void	deserializeFromFile(const std::string& filename, ISerializable & obj) const = 0;
  virtual void	deserializeFromString(const std::string& buffer, ISerializable & obj) const = 0;

};

#endif /* ISERIALIZER_HH */
