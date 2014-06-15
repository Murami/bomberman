//
// Player.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:32:20 2014 quentin desabre
// Last update Sun Jun 15 08:32:21 2014 Desabre Quentin
//

#ifndef PLAYER_HH
# define PLAYER_HH

# include "game/APlayer.hh"
# include "game/PlayerConfig.hh"

namespace bbm
{
  class	Player : public APlayer, public IEventListener
  {
  public:
    Player(GameState& gameState, const PlayerConfig& playerConfig);
    Player(GameState& gameState, const PlayerConfig& playerConfig,
	   glm::vec2 position, int power, int nbBombs, int bBombsBonus,
	   float speed, bool alive, bool slow, bool dark, BombType typeBomb,
	   PlayerState state, int score);
    ~Player();

    void		handleEvents(float time, const Input& input);
    void		update(float time);
    const std::string&  getType() const;
    void                initPosition(int x, int y);
    PlayerConfig&	getPlayerConfig();
    void		initialize();

  private:
    PlayerConfig	_playerConfig;
  };
};

#endif /* PLAYER_HH */
