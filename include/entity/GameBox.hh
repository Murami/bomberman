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
    GameBox(const glm::vec2& pos, GameState& gameState);
    ~GameBox();

    void			update(float time);
    bool			expired() const;
    void			draw(ARenderer& render, const RenderState& renderState);

    void			collideEntity();
    bool			collide(const glm::vec3 & pos);
    void			interact(AEntity *);
    const std::string &		getType() const;

    void			pack(ISerializedNode & current) const;
    void			unpack(const ISerializedNode & current);

  private:
    glm::vec2			_pos;
    std::string			_type;
    Wall			_wall;
    GameState&			_gameState;
    bool			_used;
  };
};

#endif /* GAMEBOX_HH */
