//
// ISerializedNode.hh for  in /home/pinon_a/rendu/cpp_bomberman/test/test
//
// Made by pinon
// Login   <pinon_a@epitech.net>
//
// Started on  Wed May 21 15:37:24 2014 pinon
// Last update Sun Jun 15 13:13:15 2014 otoshigami
//

#ifndef		ISERIALIZEDNODE_HH
# define	ISERIALIZEDNODE_HH

# include	<string>
# include	<glm/glm.hpp>
# include	"serializer/ISerializable.hh"

class ISerializedNode
{
public:
  ~ISerializedNode() {};

  virtual void			add(const std::string& index, const ISerializable& value) = 0;
  virtual void                  add(const std::string& index, const glm::ivec2& value) = 0;
  virtual void                  add(const std::string& index, const glm::ivec3& value) = 0;
  virtual void                  add(const std::string& index, const glm::ivec4& value) = 0;
  virtual void                  add(const std::string& index, const glm::vec2& value) = 0;
  virtual void                  add(const std::string& index, const glm::vec3& value) = 0;
  virtual void                  add(const std::string& index, const glm::vec4& value) = 0;
  virtual void			add(const std::string& index, const std::string& value) = 0;
  virtual void			add(const std::string& index, bool value) = 0;
  virtual void			add(const std::string& index, int value) = 0;
  virtual void			add(const std::string& index, unsigned int value) = 0;
  virtual void			add(const std::string& index, double value) = 0;
  virtual void			add(const std::string& index, float value) = 0;
  virtual ISerializedNode*	add(const std::string& index) = 0;

  virtual void			get(const std::string& index, ISerializable& value) const = 0;
  virtual void                  get(const std::string& index, glm::ivec2& value) const = 0;
  virtual void                  get(const std::string& index, glm::ivec3& value) const = 0;
  virtual void                  get(const std::string& index, glm::ivec4& value) const = 0;
  virtual void                  get(const std::string& index, glm::vec2& value) const = 0;
  virtual void                  get(const std::string& index, glm::vec3& value) const = 0;
  virtual void                  get(const std::string& index, glm::vec4& value) const = 0;
  virtual void			get(const std::string& index, std::string& value) const = 0;
  virtual void			get(const std::string& index, int& value) const = 0;
  virtual void			get(const std::string& index, unsigned int& value) const = 0;
  virtual void			get(const std::string& index, double& value) const = 0;
  virtual void			get(const std::string& index, float& value) const = 0;
  virtual void			get(const std::string& index, bool& value) const = 0;
  virtual ISerializedNode*	get(const std::string& index) const = 0;

  virtual int			size() const = 0;
};

#endif
