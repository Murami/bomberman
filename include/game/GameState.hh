//
// GameState.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:23 2014 otoshigami
// Last update Sun Jun 15 12:55:37 2014 otoshigami
//

#ifndef GAMESTATE_HH
# define GAMESTATE_HH

# include <vector>
# include <list>
# include <map>

# include "menu/Skybox.hh"

# include "game/IGameState.hh"
# include "game/TileMap.hh"
# include "game/AI.hh"
# include "game/GameLoadingState.hh"

# include "entity/Player.hh"

# include "graphic/Transform.hh"

# include "serializer/ISerializable.hh"

namespace bbm
{
  class	Screen;
  class GameManager;
  class AEntity;
  class IDrawable;
  class IEventListener;
  class Player;
  class HUD;

  class	GameState : public IGameState, public ISerializable
  {
  public:
    struct				GameStateConfig
    {
      bool				load;
      std::vector<PlayerConfig>		playersConfigs;
      std::vector<PlayerConfig>		AIConfigs;
    };

  public:
    typedef std::list<AEntity*>::iterator	EntitiesIt;
    typedef std::list<Player*>::iterator	PlayerIt;

  public:
    GameState(GameManager& manager, GameStateConfig* config, GameLoadingState::GameConfig*);
    ~GameState();

    void			initialize();
    void			obscuring();
    void			revealing();
    void			release();
    void			update(float time, const Input& input);
    bool			updateAIPlayer(float time, const Input& input);
    void			updateEntity(float time, const Input& input);
    void			draw(float time, Screen& context);

    void			randomize(int x, int y);
    void			load(const std::string & file);
    void			save(const std::string & file);
    void			pack(ISerializedNode & current) const;
    void			unpack(const ISerializedNode & current);
    void			addEntity(AEntity* entity);

    std::list<AEntity*>&	getEntities();
    std::vector<AEntity*>&	getGameBoxes();
    std::vector<AEntity*>&	getWarning();
    const glm::ivec2&		getMapSize() const;
    APlayer&			getPlayer(unsigned int id);

    std::list<Player*>&		getPlayerList();
    std::list<AI*>&		getAIList();

    TileMap&			getTileMap();

  private:
    void			splitScreen(Screen &, Transform&, PlayerIt);
    void			drawPlayer(Screen &, RenderState& state, PlayerIt);
    void			drawAI(Screen &, RenderState& state);
    void			drawGameBoxes(Screen &, RenderState & statex, PlayerIt);
    void			drawEntity(Screen &, RenderState & state, PlayerIt);

  private:
    Skybox				_skybox;
    bool				_flush;
    std::list<AEntity*>			_entities;
    std::list<Player*>			_players;
    std::vector<HUD*>			_huds;
    std::list<AI*>			_AIs;
    std::vector<AEntity*>		_gameboxes;
    std::vector<AEntity*>		_warning;
    std::vector<AEntity*>		_bonus;
    glm::ivec2				_mapsize;
    TileMap				_tilemap;
    std::string				_tilemapName;
    GameManager&			_manager;
    GameLoadingState::GameConfig*	_gameConfig;
    GameStateConfig*			_config;
    bool				_printHud;
  };
};

#endif /* GAMESTATE_HH */
