//
// ABomb.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:33 2014 quentin desabre
// Last update Sun Jun 15 08:33:33 2014 Desabre Quentin
//

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
    ABomb(GameState& gameState);
    ABomb(const glm::vec2& postion, GameState& gameState, unsigned int idPlayer);
    ~ABomb();

    virtual void			update(float time) = 0;
    virtual bool			expired() const = 0;
    virtual void			interact(AEntity *) = 0;
    virtual bool			collide(const glm::vec3&) = 0;
    virtual const std::string &		getType() const = 0;
    virtual void			setLifeSpan(float);
    virtual void			initialize() = 0;

    const glm::vec2&			getPosition() const;

  protected:
    GameState&				_gameState;
    bool				_used;
    bool				_playerIsOver;
    float				_lifespan;
    float				_anim;
  };
};

#endif		/* ABOMV_HH_ */
