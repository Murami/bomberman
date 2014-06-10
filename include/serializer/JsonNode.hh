#ifndef JSON_NODE_HH
#define JSON_NODE_HH

#include <vector>
#include "json/json.h"
#include "serializer/ISerializedNode.hh"
#include "serializer/SerializerException.hh"

class JsonNode : public ISerializedNode
{
public:
  JsonNode(Json::Value& current);
  virtual ~JsonNode();

  void			add(const std::string& index, const ISerializable& serialiable);
  void                  add(const std::string& index, const glm::ivec2& value);
  void                  add(const std::string& index, const glm::ivec3& value);
  void                  add(const std::string& index, const glm::ivec4& value);
  void                  add(const std::string& index, const glm::vec2& value);
  void                  add(const std::string& index, const glm::vec3& value);
  void                  add(const std::string& index, const glm::vec4& value);
  void			add(const std::string& index, const std::string& value);
  void			add(const std::string& index, int value);
  void			add(const std::string& index, double value);
  void			add(const std::string& index, float value);
  ISerializedNode*	add(const std::string& index);

  void			get(const std::string& index, ISerializable& serializable) const;
  void                  get(const std::string& index, glm::ivec2& value) const;
  void                  get(const std::string& index, glm::ivec3& value) const;
  void                  get(const std::string& index, glm::ivec4& value) const;
  void                  get(const std::string& index, glm::vec2& value) const;
  void                  get(const std::string& index, glm::vec3& value) const;
  void                  get(const std::string& index, glm::vec4& value) const;
  void			get(const std::string& index, std::string& value) const;
  void			get(const std::string& index, int& value) const;
  void			get(const std::string& index, double& value) const;
  void			get(const std::string& index, float& value) const;
  void                  get(const std::string& index, bool& value) const;
  ISerializedNode*      get(const std::string& index) const;

  void			set(const std::string& index, const ISerializable& value);
  void			set(const std::string& index, const std::string& value);
  void			set(const std::string& index, int value);
  void			set(const std::string& index, double value);
  void			set(const std::string& index, float value);

  int			size() const;

private:
  Json::Value&			_current;
};

#endif
