//
// MultiBomb.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:58 2014 quentin desabre
// Last update Sun Jun 15 08:33:58 2014 Desabre Quentin
//

#ifndef MULTIBOMB_HH
#define MULTIBOMB_HH

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

  class	MultiBomb : public ABomb
  {
  public:
    MultiBomb(GameState & GameState);
    MultiBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer);
    ~MultiBomb();

    void		interact(AEntity *);
    void		initialize();
    void		update(float time);
    bool		collide(const glm::vec3&);
    bool		expired() const;
    const std::string &	getType() const;

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    bool		addExplode(float x, float y);

  private:
    Model		_model;
  };
};

#endif /* MULTIBOMB_HH */
