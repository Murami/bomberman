//
// JsonSerializer.hh for  in /home/pinon_a/rendu/cpp_bomberman/test/test
//
// Made by pinon
// Login   <pinon_a@epitech.net>
//
// Started on  Mon May 26 09:09:04 2014 pinon
// Last update Mon Jun  2 18:01:37 2014 pinon
//

#ifndef JSON_SERIALIZER_HH
# define JSON_SERIALIZER_HH

#include <string>
#include <fstream>
#include <json/json.h>
# include "serializer/ISerializer.hh"

class ISerializable;

class JSONSerializer : public ISerializer
{
public:
  JSONSerializer();
  ~JSONSerializer();

  void	serializeToFile(const std::string& filename, ISerializable & obj) const;
  void	serializeToString(const std::string& buffer, ISerializable & obj) const;

  void	deserializeFromFile(const std::string& filename, ISerializable & obj) const;
  void	deserializeFromString(const std::string& buffer, ISerializable & obj) const;
};

#endif
