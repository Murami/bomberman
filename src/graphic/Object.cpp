#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <Texture.hh>
#include <BasicShader.hh>
#include "graphic/Object.hh"
#include "graphic/ARenderer.hh"
#include "graphic/Transform.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/RenderState.hh"
#include "serializer/ISerializedNode.hh"

namespace bbm
{
  Object::Object()
  {
    _texture = NULL;
    _shader = NULL;
    _needBuild = false;
  }

  Object::Object(const std::string& texture,
		 const std::string& shader,
		 int primitive)
  {
    setTexture(texture);
    setShader(shader);
    _primitive = primitive;
    _needBuild = false;
  }

  Object::~Object()
  {
  }


  void Object::initialize(const std::string& texture,
			  const std::string& shader,
			  const std::string& primitive)
  {
    _textureName = texture;
    _shaderName = shader;
    _primitiveName = primitive;
    setTexture(_textureName);
    setShader(_shaderName);
    _primitive = bbm::IDrawable::primitives.at(_primitiveName);
  }

  void	Object::setPrimitive(int primitive)
  {
    _primitive = primitive;
  }

  void	Object::draw(ARenderer& renderer, const RenderState& renderState)
  {
    RenderState	newState = renderState;

    newState.transform = getTransform() * renderState.transform;
    renderer.draw(_geometry, _texture, _shader, newState, _primitive, glm::vec4(1, 1, 1, 1));
  }

  void	Object::setTexture(const std::string& texture)
  {
    _texture = TextureManager::getInstance()->getTexture(texture);
  }

  void	Object::setShader(const std::string& shader)
  {
    _shader = ShaderManager::getInstance()->getShader(shader);
  }

  void	Object::setColor(const glm::vec4& color)
  {
    _geometry.setColor(color);
  }

  void	Object::pushVertex(const glm::vec3& vertex)
  {
    _geometry.pushVertex(vertex);
    _needBuild = true;
  }

  void	Object::pushUv(const glm::vec2& uv)
  {
    _geometry.pushUv(uv);
    _needBuild = true;
  }

  void	Object::build()
  {
    if (_needBuild)
      {
	_geometry.build();
	_needBuild = false;
      }
  }

  void	Object::pack(ISerializedNode & current) const
  {
    current.add("texture", _textureName);
    current.add("shader", _shaderName);
    current.add("primitive", _primitiveName);
  }

  void	Object::unpack(const ISerializedNode & current)
  {
    current.get("texture", _textureName);
    current.get("shader", _shaderName);
    current.get("primitive", _primitiveName);
    setTexture(_textureName);
    setShader(_shaderName);
    _primitive = bbm::IDrawable::primitives.at(_primitiveName);
  }
};
