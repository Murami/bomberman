//
// ABombExplode.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:36 2014 quentin desabre
// Last update Sun Jun 15 08:33:37 2014 Desabre Quentin
//

#ifndef		_ABOMBEXPLODE_HH_
# define	_ABOMBEXPLODE_HH_

# include	"entity/AEntity.hh"

namespace bbm
{
  class GameState;

  class ABombExplode : public AEntity
  {
  public:
    ABombExplode(GameState& gameState);
    ABombExplode(const glm::vec2& position, GameState& gameState);
    ~ABombExplode();

    virtual bool                        expired() const = 0;
    virtual void                        interact(AEntity *) = 0;
    virtual bool                        collide(const glm::vec3&) = 0;
    virtual void                        update(float time) = 0;
    virtual void                        setLifeSpan(float);
    virtual void			initialize() = 0;
    virtual const std::string &         getType() const = 0;
    const glm::vec2&			getPosition() const;

  protected:
    GameState&		_gameState;
    float		_lifespan;
  };
};

#endif		/* _ABOMBEXPLODE_HH_ */
