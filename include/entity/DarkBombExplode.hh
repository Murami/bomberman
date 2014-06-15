//
// DarkBombExplode.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:46 2014 quentin desabre
// Last update Sun Jun 15 08:33:47 2014 Desabre Quentin
//

#ifndef DARKBOMBEXPLODE_HH
#define DARKBOMBEXPLODE_HH

#include "entity/ABombExplode.hh"
#include "game/Wall.hh"

namespace bbm
{
  class	ARenderer;
  class RenderState;
  class	GameState;

  class	DarkBombExplode : public ABombExplode
  {
  public:
    DarkBombExplode(GameState & GameState);
    DarkBombExplode(const glm::vec2& position, GameState& gameState);
    ~DarkBombExplode();

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

#endif /* DARKBOMBEXPLODE_HH */
