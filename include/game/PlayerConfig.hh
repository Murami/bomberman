#ifndef PLAYER_CONFIG_HH
#define PLAYER_CONFIG_HH

#include "game/APlayer.hh"

namespace bbm
{
  class InputConfig;

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
    unsigned int	idPlayer;
    unsigned int	id;
    unsigned int	lastId;
    int			score;
    int			idGamepad;
    std::string*	IALevel;
  };
};

#endif /* PLAYER_CONFIG_HH */
