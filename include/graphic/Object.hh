#ifndef GRAPHICOBJECT_HH
#define GRAPHICOBJECT_HH

#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include "graphic/IDrawable.hh"
#include "graphic/Transformable.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class	RenderState;

  class	Object : public IDrawable, public Transformable, public ISerializable
  {
  private:
    gdl::Geometry		_geometry;
    gdl::Texture*		_texture;
    gdl::BasicShader*		_shader;
    int				_primitive;
    bool			_needBuild;

  private:
    std::string			_textureName;
    std::string			_shaderName;
    std::string			_primitiveName;

  public:
    Object(const std::string& texture,
	   const std::string& shader,
	   int primitive);
    Object();

    virtual ~Object();

    void		setPrimitive(int primitive);
    void		setTexture(const std::string& texture);
    void		setShader(const std::string& shader);
    void		setColor(const glm::vec4& color);
    void		pushVertex(const glm::vec3& vertex);
    void		pushUv(const glm::vec2& uv);
    void		build();

    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);
  };
};

#endif /* GRAPHICOBJECT_HH */
