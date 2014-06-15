//
// WaterBonus.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:32:11 2014 quentin desabre
// Last update Sun Jun 15 08:32:12 2014 Desabre Quentin
//

#ifndef WATERBONUS_HH
#define WATERBONUS_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class RenderState;

  class	WaterBonus : public AEntity
  {
  public:
    WaterBonus();
    WaterBonus(const glm::vec2& pos);
    ~WaterBonus();

    void		update(float time);
    void		initialize();
    void		interact(AEntity *);
    bool		expired() const;
    bool		collide(const glm::vec3&);
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

#endif /* WATERBONUS_HH */
