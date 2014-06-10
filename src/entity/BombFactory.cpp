#include <cstdlib>
#include "entity/BombFactory.hh"
#include "entity/AEntity.hh"

#include "entity/FireBomb.hh"
#include "entity/BoxBomb.hh"
#include "entity/MultiBomb.hh"
#include "entity/PowerBomb.hh"
#include "entity/DarkBomb.hh"
#include "entity/WaterBomb.hh"

namespace bbm
{
  std::map<BombType, BombFactory::FactoryMethod>	create_mapFactory()
  {
    std::map<BombType, BombFactory::FactoryMethod>	map;

    map[FIRE] = &BombFactory::createFireBomb;
    map[BOX] = &BombFactory::createBoxBomb;
    map[WATER] = &BombFactory::createWaterBomb;
    map[MULTI] = &BombFactory::createMultiBomb;
    map[DARK] = &BombFactory::createDarkBomb;
    map[POWER] = &BombFactory::createPowerBomb;

    return (map);
  }

  std::map<BombType, BombFactory::FactoryMethod>	BombFactory::_map = create_mapFactory();
  BombFactory *						BombFactory::_instance = NULL;


  BombFactory::BombFactory()
  {
  }

  BombFactory::~BombFactory()
  {
  }

  BombFactory*		BombFactory::getInstance()
  {
    if (_instance == NULL)
      _instance = new BombFactory();
    return (_instance);
  }

  void			BombFactory::delInstance()
  {
    if (_instance != NULL)
      {
	_instance = NULL;
	delete (_instance);
      }
  }

  AEntity*	       	BombFactory::create(BombType type,
					    const glm::vec2& position,
					    GameState& gameState,
					    unsigned int idPlayer)
  {
    return ((this->*_map[type])(position, gameState, idPlayer));
  }

  AEntity*	       	BombFactory::createRandom(const glm::vec2 & pos, GameState& gameState, unsigned int idPlayer)
  {
    BombType		tmp;

    tmp = FIRE;
    while (tmp == FIRE || tmp == RANDOM)
      tmp = static_cast<BombType>(std::rand() % (_map.size() - 1));
    return ((this->*_map[tmp])(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createPowerBomb(const glm::vec2 & pos,
						     GameState& gameState,
						     unsigned int idPlayer)
  {
    return (new PowerBomb(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createWaterBomb(const glm::vec2 & pos,
						     GameState& gameState,
						     unsigned int idPlayer)
  {
    return (new WaterBomb(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createFireBomb(const glm::vec2 & pos,
						    GameState& gameState,
						    unsigned int idPlayer)
  {
    return (new FireBomb(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createDarkBomb(const glm::vec2 & pos,
						    GameState& gameState,
						    unsigned int idPlayer)
  {
    return (new DarkBomb(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createBoxBomb(const glm::vec2 & pos,
						   GameState& gameState,
						   unsigned int idPlayer)
  {
    return (new BoxBomb(pos, gameState, idPlayer));
  }

  AEntity*		BombFactory::createMultiBomb(const glm::vec2 & pos,
						     GameState& gameState,
						     unsigned int idPlayer)
  {
    return (new MultiBomb(pos, gameState, idPlayer));
  }
}
