#ifndef		_ABOMB_HH_
# define	_ABOMB_HH_

# include	<glm/glm.hpp>
# include	"entity/AEntity.hh"
# include	"graphic/Utils.hh"

namespace bbm
{
  class GameState;

class	ABomb : public AEntity
  {

  public:
    ABomb(const glm::vec2& postion, GameState& gameState, unsigned int idPlayer);
    ~ABomb();

    virtual void			update(float time) = 0;
    virtual bool			expired() const = 0;
    virtual void			interact(AEntity *) = 0;
    virtual bool			collide(const glm::vec3&) = 0;
    virtual const std::string &		getType() const = 0;
    virtual void			setLifeSpan(float);

    virtual void			pack(ISerializedNode & current) const = 0;
    virtual void			unpack(const ISerializedNode & current) = 0;

  protected:
    glm::vec3				_position;
    GameState&				_gameState;
    unsigned int			_idPlayer;
    bool				_used;
    bool				_playerIsOver;
    float				_lifespan;
  };
};

#endif		/* ABOMV_HH_ */
