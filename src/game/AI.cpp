#include "game/AI.hh"

namespace bbm
{
  AI::AI(GameState& gameState) :
    APlayer(gameState)
  {
    _type = "AI";
  }

  AI::~AI()
  {
  }

  void	AI::update(float time)
  {
    (void) time;
  }

  void  AI::pack(ISerializedNode & current) const
  {
    (void) current;
  }

  void  AI::unpack(const ISerializedNode & current)
  {
    (void) current;
  }

  const std::string&	AI::getType() const
  {
    return (_type);
  }
};
