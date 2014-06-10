//
// JsonSerializer.cpp for  in /home/pinon_a/rendu/cpp_bomberman/test/test
//
// Made by pinon
// Login   <pinon_a@epitech.net>
//
// Started on  Mon May 26 09:13:28 2014 pinon
// Last update Mon Jun  2 17:58:40 2014 pinon
//

#include <sstream>
#include <iostream>
#include "serializer/JSONSerializer.hh"
#include "serializer/JsonNode.hh"

JSONSerializer::JSONSerializer()
{

}

JSONSerializer::~JSONSerializer()
{

}

void	JSONSerializer::serializeToFile(const std::string& filename, ISerializable & obj) const
{
  Json::Value		root;
  Json::Reader		reader;
  std::filebuf		fb;

  fb.open (filename.c_str(), std::ios::out | std::ios::trunc);
  std::ostream os(&fb);

  JsonNode		node(root);
  obj.pack(node);
  os << root.toStyledString();
}

void	JSONSerializer::serializeToString(const std::string& buffer, ISerializable & obj) const
{
  Json::Value		root;
  Json::Reader		reader;
  JsonNode		node(root);

  obj.pack(node);
  buffer + root.toStyledString();
}

void	JSONSerializer::deserializeFromFile(const std::string& filename, ISerializable & obj) const
{
  Json::Value	root;
  Json::Reader	reader;
  std::filebuf	fb;

  fb.open (filename.c_str(), std::ios::in);
  std::istream is(&fb);
  bool parsingSuccessful = reader.parse( is, root, false );
  if ( !parsingSuccessful )
    throw SerializerException("Failed to parse configuration\n" + reader.getFormatedErrorMessages());
  obj.unpack(JsonNode(root));
}

void	JSONSerializer::deserializeFromString(const std::string& buffer, ISerializable & obj) const
{
  Json::Value root;
  Json::Reader reader;
  std::stringstream ss;

  ss << buffer;
  bool parsingSuccessful = reader.parse( ss, root, false );
  if ( !parsingSuccessful )
    throw SerializerException("Failed to parse configuration\n" + reader.getFormatedErrorMessages());
  obj.unpack(JsonNode(root));
}
