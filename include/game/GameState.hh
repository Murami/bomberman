#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include <list>
#include <map>
#include "game/IGameState.hh"
#include "game/TileMap.hh"
#include "graphic/Transform.hh"
#include "entity/Player.hh"
#include "game/AI.hh"
#include "menu/Skybox.hh"
#include "serializer/ISerializable.hh"

namespace bbm
{
  class	Screen;
  class GameManager;
  class AEntity;
  class IDrawable;
  class IEventListener;
  class Player;

  class	GameState : public IGameState, public ISerializable
  {
  public:
    struct				GameStateConfig
    {
      std::vector<PlayerConfig>		playersConfigs;
    };

  public:
    typedef std::list<AEntity*>::iterator	EntitiesIt;
    typedef std::list<Player*>::iterator	PlayerIt;

  public:
    GameState(GameManager& manager, GameStateConfig* config);
    ~GameState();

    void			initialize();
    void			obscuring();
    void			revealing();
    void			release();
    void			update(float time, const Input& input);
    void			draw(float time, Screen& context);

    void			randomize(int x, int y);
    void			load(const std::string & file);
    void			save(const std::string & file);
    void			pack(ISerializedNode & current) const;
    void			unpack(const ISerializedNode & current);

    void			addEntity(AEntity* entity);
    std::list<AEntity*>&	getEntities();
    Player&			getPlayer(unsigned int id);

    std::list<Player*>&		getPlayerList();

    TileMap&			getTileMap();

  private:
    Skybox	_skybox;
    bool	_flush;
    std::list<AEntity*>		_entities;
    std::list<Player*>		_players;
    std::list<AI*>		_AIs;
    TileMap			_tilemap;
    std::string			_tilemapName;
    GameManager&		_manager;
    GameStateConfig*		_config;
  };
};

#endif /* GAMESTATE_HH */
