//
// SpeedBonus.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:34:05 2014 quentin desabre
// Last update Sun Jun 15 08:34:06 2014 Desabre Quentin
//

#ifndef SPEEDBONUS_HH
#define SPEEDBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	SpeedBonus : public AEntity
  {
  public:
    SpeedBonus();
    SpeedBonus(const glm::vec2& pos);
    ~SpeedBonus();

    void		initialize();
    void		update(float time);
    void		interact(AEntity *);
    bool		collide(const glm::vec3&);
    bool		expired() const;
    const glm::vec2&	getPosition() const;
    const std::string&	getType() const;

  protected:
    void		draw(ARenderer& render, const RenderState& renderState);

  private:
    float		_anim;
    Wall		_wall;
    bool		_used;
  };
};

#endif /* SPEEDBONUS_HH */
