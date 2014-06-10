#ifndef PLAYER_CONFIG_HH
#define PLAYER_CONFIG_HH

namespace bbm
{
  struct PlayerConfig
  {
    InputConfig*	inputConfig;
    glm::ivec2		splitScreenPosition;
    glm::ivec2		splitScreenSize;
  };
};

#endif /* PLAYER_CONFIG_HH */
