#ifndef AI_HH
#define AI_HH

#include "game/APlayer.hh"

namespace bbm
{
  class	AI : public APlayer
  {
  public:
    AI(GameState& gameState);
    ~AI();

    void		update(float time);
    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);
    const std::string&	getType() const;

  private:
    std::string	_type;
  };
};

#endif /* AI_HH */
