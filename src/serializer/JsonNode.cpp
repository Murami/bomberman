#include <string>
#include <iostream>
#include "serializer/JsonNode.hh"

JsonNode::JsonNode(Json::Value& current) : _current(current)
{

}

JsonNode::~JsonNode()
{

}

//ADD

void			JsonNode::add(const std::string& index, const ISerializable& serializable)
{
  JsonNode node(_current[index]);

  serializable.pack(node);
}


void			JsonNode::add(const std::string& index, const glm::ivec2& value)
{
  JsonNode node(_current[index]);

  node.add("x", value.x);
  node.add("y", value.y);
}

void			JsonNode::add(const std::string& index, const glm::ivec3& value)
{
  JsonNode node(_current[index]);

  node.add("x", value.x);
  node.add("y", value.y);
  node.add("z", value.z);
}

void			JsonNode::add(const std::string& index, const glm::ivec4& value)
{
  JsonNode node(_current[index]);

  node.add("r", value.r);
  node.add("g", value.g);
  node.add("b", value.b);
  node.add("a", value.a);
}


void			JsonNode::add(const std::string& index, const glm::vec2& value)
{
  JsonNode node(_current[index]);

  node.add("x", value.x);
  node.add("y", value.y);
}

void			JsonNode::add(const std::string& index, const glm::vec3& value)
{
  JsonNode node(_current[index]);

  node.add("x", value.x);
  node.add("y", value.y);
  node.add("z", value.z);
}

void			JsonNode::add(const std::string& index, const glm::vec4& value)
{
  JsonNode node(_current[index]);

  node.add("r", value.r);
  node.add("g", value.g);
  node.add("b", value.b);
  node.add("a", value.a);
}

void			JsonNode::add(const std::string& index, const std::string& value)
{
  _current[index] = value;
}

void			JsonNode::add(const std::string& index, int value)
{
  _current[index] = value;
}

void			JsonNode::add(const std::string& index, bool value)
{
  _current[index] = value;
}

void			JsonNode::add(const std::string& index, unsigned int value)
{
  _current[index] = value;
}

void			JsonNode::add(const std::string& index, double value)
{
  _current[index] = value;
}

void			JsonNode::add(const std::string& index, float value)
{
  _current[index] = value;
}

ISerializedNode*	JsonNode::add(const std::string& index)
{
  _current[index] = Json::Value();
  return (new JsonNode(_current[index]));
}

//GET

void			JsonNode::get(const std::string& index, ISerializable& serializable) const
{
  try
    {
      serializable.unpack(JsonNode(_current[index]));
    }
  catch (SerializerException& ex)
    {
      throw SerializerException("[" + index + "] " + ex.what());
    }
}

void			JsonNode::get(const std::string& index, glm::ivec2& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
}

void			JsonNode::get(const std::string& index, glm::ivec3& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
  node.get("z", value.z);
}

void			JsonNode::get(const std::string& index, glm::ivec4& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
  node.get("z", value.z);
  node.get("y", value.y);
}

void			JsonNode::get(const std::string& index, glm::vec2& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
}

void			JsonNode::get(const std::string& index, glm::vec3& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
  node.get("z", value.z);
}

void			JsonNode::get(const std::string& index, glm::vec4& value) const
{
  JsonNode node(_current[index]);

  node.get("x", value.x);
  node.get("y", value.y);
  node.get("z", value.z);
  node.get("y", value.y);
}

void			JsonNode::get(const std::string& index, std::string& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isString())
    throw SerializerException("[" + index + "] is not a string type");
  value = _current[index].asString();
}

void			JsonNode::get(const std::string& index, int& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isInt() && !_current[index].isDouble())
    throw SerializerException("[" + index + "] is not an int type");
  value = _current[index].asInt();
}

void			JsonNode::get(const std::string& index, unsigned int& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isUInt() && !_current[index].isInt())
    throw SerializerException("[" + index + "] is not an unsigned int type");
  value = _current[index].asInt();
}

void			JsonNode::get(const std::string& index, double& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isDouble() && !_current[index].isInt())
    throw SerializerException("[" + index + "] is not a double type");
  value = _current[index].asDouble();
}

void			JsonNode::get(const std::string& index, float& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isDouble() && !_current[index].isInt())
    throw SerializerException("[" + index + "] is not a double type");
  value = _current[index].asDouble();
}

void			JsonNode::get(const std::string& index, bool& value) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  if (!_current[index].isBool())
    throw SerializerException("[" + index + "] is not a bool type");
  value = _current[index].asBool();
}

ISerializedNode*	JsonNode::get(const std::string& index) const
{
  if (!_current.isMember(index))
    throw SerializerException("[" + index + "] doesn't exist");
  return(new JsonNode(_current[index]));
}

int JsonNode::size() const
{
  return (_current.size());
}
