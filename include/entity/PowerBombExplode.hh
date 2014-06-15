//
// PowerBombExplode.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:34:00 2014 quentin desabre
// Last update Sun Jun 15 08:34:01 2014 Desabre Quentin
//

#ifndef POWERBOMBEXPLODE_HH
#define POWERBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	PowerBombExplode : public ABombExplode
  {
  public:
    PowerBombExplode(GameState & GameState);
    PowerBombExplode(const glm::vec2& position, GameState& gameState, unsigned int id);
    ~PowerBombExplode();

    void			initialize();
    void			update(float time);
    void			interact(AEntity *);
    void			collideEntity();
    void			collideGameBoxes();
    void			setLifespan(float);
    bool			collide(const glm::vec3&);
    bool			expired() const;
    const std::string &		getType() const;

  protected:
    void			draw(ARenderer& renderer, const RenderState& renderState);

  private:
    Wall		       	_wall;
  };
};

#endif /* POWERBOMBEXPLODE_HH */
