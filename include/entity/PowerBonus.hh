//
// PowerBonus.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:34:03 2014 quentin desabre
// Last update Sun Jun 15 08:34:03 2014 Desabre Quentin
//

#ifndef POWERBONUS_HH
#define POWERBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	PowerBonus : public AEntity
  {
  public:
    PowerBonus();
    PowerBonus(const glm::vec2& pos);
    ~PowerBonus();

    void		initialize();
    void		update(float time);
    void		draw(ARenderer& render, const RenderState& renderState);
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);
    bool		expired() const;
    const glm::vec2&	getPosition() const;
    const std::string&	getType() const;

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* POWERBONUS_HH */
