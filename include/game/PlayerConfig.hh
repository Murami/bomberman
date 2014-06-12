#ifndef PLAYER_CONFIG_HH
#define PLAYER_CONFIG_HH

#include "game/APlayer.hh"

namespace bbm
{
  struct PlayerConfig
  {
    InputConfig*	inputConfig;
    glm::vec2		position;
    int			power;
    int			nbBombs;
    int			nbBombsBonus;
    float      		speed;
    bool		alive;
    bool		slow;
    bool		dark;
    BombType		typeBomb;
    PlayerState		state;
    int			score;
  };
};

#endif /* PLAYER_CONFIG_HH */
