//
// PowerBomb.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:32:18 2014 quentin desabre
// Last update Sun Jun 15 08:32:18 2014 Desabre Quentin
//

#ifndef POWERBOM_HH
#define POWERBOM_HH

#include "graphic/IDrawable.hh"
#include "graphic/Model.hh"
#include "entity/ABomb.hh"
#include "entity/AEntity.hh"
#include "entity/Player.hh"

namespace bbm
{
  class	ARenderer;
  class	RenderState;
  class	GameState;

  class	PowerBomb : public ABomb
  {
  public:
    PowerBomb(GameState & GameState);
    PowerBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~PowerBomb();

    void		update(float time);
    bool		expired() const;
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    void		initialize();

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    bool		addExplode(float x, float y);

  private:
    Model		_model;
  };
};

#endif /* POWERBOM_HH */
