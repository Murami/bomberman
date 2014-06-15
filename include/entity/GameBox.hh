//
// GameBox.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:32:27 2014 quentin desabre
// Last update Sun Jun 15 08:34:15 2014 Desabre Quentin
//

#ifndef GAMEBOX_HH
#define GAMEBOX_HH

#include "game/Wall.hh"
#include "entity/AEntity.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class ARenderer;
  class GameState;
  class RenderState;

  class	GameBox : public AEntity
  {
  public:
    GameBox(GameState& gameState);
    GameBox(const glm::vec2& pos, int idPLayer, GameState& gameState);
    ~GameBox();

    void			update(float time);
    bool			expired() const;
    void			draw(ARenderer& render, const RenderState& renderState);

    void			collideEntity();
    bool			collide(const glm::vec3 & pos);
    void			interact(AEntity *);
    const std::string &		getType() const;

    const glm::vec2&		getPosition() const;

    void			initialize();

  private:
    Wall			_wall;
    GameState&			_gameState;
    bool			_used;
  };
};

#endif /* GAMEBOX_HH */
