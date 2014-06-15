//
// ISerializer.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:23:03 2014 Manu
// Last update Sun Jun 15 13:23:03 2014 Manu
//

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
