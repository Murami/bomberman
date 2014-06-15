//
// FireBombExplode.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:51 2014 quentin desabre
// Last update Sun Jun 15 08:33:51 2014 Desabre Quentin
//

#ifndef FIREBOMBEXPLODE_HH
#define FIREBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	FireBombExplode : public ABombExplode
  {
  public:
    FireBombExplode(GameState & GameState);
    FireBombExplode(const glm::vec2& position, GameState& gameState, unsigned int id);
    ~FireBombExplode();

    void			initialize();
    void			update(float time);
    void			interact(AEntity *);
    void			collideEntity();
    void			collideGameBoxes();
    void			setLifespan(float);
    bool			expired() const;
    bool			collide(const glm::vec3&);
    const std::string &		getType() const;

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    Wall		       	_wall;
  };
};

#endif /* FIREBOMBEXPLODE_HH */
