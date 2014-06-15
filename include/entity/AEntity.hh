//
// AEntity.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:39 2014 quentin desabre
// Last update Sun Jun 15 08:33:39 2014 Desabre Quentin
//

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

    unsigned int		getID() const;
    unsigned int		getLastID() const;
    void			setID(unsigned int id);
    void			setLastID(unsigned int id);
    void			pack(ISerializedNode & current) const;
    void			unpack(const ISerializedNode & current);

    virtual void		update(float time) = 0;
    virtual void		interact(AEntity *) = 0;
    virtual void		initialize() = 0;
    virtual bool		expired() const = 0 ;
    virtual bool		collide(const glm::vec3&) = 0;
    virtual const glm::vec2&	getPosition() const = 0;
    virtual const std::string &	getType() const = 0;

  protected:
    virtual void		draw(ARenderer& renderer, const RenderState& renderState) = 0;
    static unsigned int		newID();

  protected:
    glm::vec2			_pos;
    std::string			_type;
    unsigned int		_idPlayer;

  private:
    static unsigned int		_lastInstanceID;
    int				_id;
  };
};

#endif /* AENTITY_HH */
