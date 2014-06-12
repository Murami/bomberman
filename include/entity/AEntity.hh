#ifndef AENTITY_HH
#define AENTITY_HH

#include "graphic/Transformable.hh"
#include "graphic/IDrawable.hh"
#include "events/IEventListener.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  extern const float collideDelta;

  class	AEntity : public IDrawable, public ISerializable
  {
  public:
    AEntity();
    virtual ~AEntity();

    unsigned int		getID();

    virtual void		update(float time) = 0;
    virtual bool		expired() const = 0 ;
    // virtual bool		collide(const IQuadTree& node);
    // virtual bool		collide(AEntity *) = 0;
    virtual bool		collide(const glm::vec3&) = 0;
    virtual const std::string &	getType() const = 0;
    virtual void		interact(AEntity *) = 0;
    virtual const glm::vec2&	getPosition() const = 0;

    virtual void		pack(ISerializedNode & current) const = 0;
    virtual void		unpack(const ISerializedNode & current) = 0;

  protected:
    virtual void		draw(ARenderer& renderer, const RenderState& renderState) = 0;
    static unsigned int		newID();

  private:
    static unsigned int		_lastInstanceID;
    int				_id;
  };
};

#endif /* AENTITY_HH */
