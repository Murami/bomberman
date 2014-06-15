//
// RandomBonus.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:32:16 2014 quentin desabre
// Last update Sun Jun 15 08:32:16 2014 Desabre Quentin
//

#ifndef RANDOMBONUS_HH
#define RANDOMBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	RandomBonus : public AEntity
  {
  public:
    RandomBonus();
    RandomBonus(const glm::vec2& pos);
    ~RandomBonus();

    void		update(float time);
    bool		expired() const;
    void		draw(ARenderer& render, const RenderState& renderState);
    const std::string &	getType() const;
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);

    const glm::vec2&	getPosition() const;


    void		initialize();

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* RANDOMBONUS_HH */
