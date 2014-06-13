#include "entity/EntityFactory.hh"

#include "entity/FireBonus.hh"
#include "entity/BoxBonus.hh"
#include "entity/BombBonus.hh"
#include "entity/MultiBombBonus.hh"
#include "entity/RandomBonus.hh"
#include "entity/PowerBonus.hh"
#include "entity/SpeedBonus.hh"
#include "entity/DarkBonus.hh"
#include "entity/WaterBonus.hh"
#include "entity/GameBox.hh"

#include "entity/FireBomb.hh"
#include "entity/BoxBomb.hh"
#include "entity/MultiBomb.hh"
#include "entity/PowerBomb.hh"
#include "entity/DarkBomb.hh"
#include "entity/WaterBomb.hh"
#include "entity/FireBombExplode.hh"
#include "entity/PowerBombExplode.hh"
#include "entity/DarkBombExplode.hh"
#include "entity/WaterBombExplode.hh"

namespace bbm
{
  std::map<std::string, EntityFactory::FactoryMethod>	createEntityMap()
  {
    std::map<std::string, EntityFactory::FactoryMethod>	map;

    map["BoxBonus"] = &EntityFactory::createBoxBonus;
    map["SpeedBonus"] = &EntityFactory::createSpeedBonus;
    map["BombBonus"] = &EntityFactory::createBombBonus;
    map["FireBonus"] = &EntityFactory::createFireBonus;
    map["WaterBonus"] = &EntityFactory::createWaterBonus;
    map["RandomBonus"] = &EntityFactory::createRandomBonus;
    map["MultiBombBonus"] = &EntityFactory::createMultiBombBonus;
    map["DarkBonus"] = &EntityFactory::createDarkBonus;
    map["PowerBonus"] = &EntityFactory::createPowerBonus;
    map["GameBox"] = &EntityFactory::createGameBox;
    map["WaterBomb"] = &EntityFactory::createWaterBomb;
    map["PowerBomb"] = &EntityFactory::createPowerBomb;
    map["BoxBomb"] = &EntityFactory::createBoxBomb;
    map["FireBomb"] = &EntityFactory::createFireBomb;
    map["MultiBomb"] = &EntityFactory::createMultiBomb;
    map["DarkBomb"] = &EntityFactory::createDarkBomb;
    map["FireBombExplode"] = &EntityFactory::createFireBombExplode;
    map["DarkBombExplode"] = &EntityFactory::createDarkBombExplode;
    map["WaterBombExplode"] = &EntityFactory::createWaterBombExplode;
    map["PowerBombExplode"] = &EntityFactory::createPowerBombExplode;

    return (map);
  }

  std::map<std::string, EntityFactory::FactoryMethod>
  EntityFactory::_map = createEntityMap();

  EntityFactory::EntityFactory()
  {

  }

  EntityFactory::~EntityFactory()
  {

  }

  AEntity*	EntityFactory::create(const std::string& type, GameState & gameState)
  {
    if (_map.find(type) == _map.end())
      return (NULL);
    else
      return ((this->*_map[type])(gameState));
  }

  AEntity*	EntityFactory::createSpeedBonus(GameState & gameState)
  {
    (void)gameState;
    return (new SpeedBonus);
  }

  AEntity*	EntityFactory::createBombBonus(GameState & gameState)
  {
    (void)gameState;
    return (new BombBonus);
  }

  AEntity*	EntityFactory::createPowerBonus(GameState & gameState)
  {
    (void)gameState;
    return (new PowerBonus);
  }

  AEntity*	EntityFactory::createWaterBonus(GameState & gameState)
  {
    (void)gameState;
    return (new WaterBonus);
  }

  AEntity*	EntityFactory::createFireBonus(GameState & gameState)
  {
    (void)gameState;
    return (new FireBonus);
  }

  AEntity*	EntityFactory::createDarkBonus(GameState & gameState)
  {
    (void)gameState;
    return (new DarkBonus);
  }

  AEntity*	EntityFactory::createBoxBonus(GameState & gameState)
  {
    (void)gameState;
    return (new BoxBonus);
  }

  AEntity*	EntityFactory::createRandomBonus(GameState & gameState)
  {
    (void)gameState;
    return (new RandomBonus);
  }

  AEntity*	EntityFactory::createMultiBombBonus(GameState & gameState)
  {
    (void)gameState;
    return (new MultiBombBonus);
  }

  AEntity*	EntityFactory::createGameBox(GameState & gameState)
  {
    return (new GameBox(gameState));
  }


  AEntity*	EntityFactory::createPowerBomb(GameState & gameState)
  {
    return (new PowerBomb(gameState));
  }

  AEntity*	EntityFactory::createWaterBomb(GameState & gameState)
  {
    return (new WaterBomb(gameState));
  }

  AEntity*	EntityFactory::createFireBomb(GameState & gameState)
  {
    return (new FireBomb(gameState));
  }

  AEntity*	EntityFactory::createDarkBomb(GameState & gameState)
  {
    return (new DarkBomb(gameState));
  }

  AEntity*	EntityFactory::createBoxBomb(GameState & gameState)
  {
    return (new BoxBomb(gameState));
  }

  AEntity*	EntityFactory::createMultiBomb(GameState & gameState)
  {
    return (new MultiBomb(gameState));
  }

  AEntity*	EntityFactory::createDarkBombExplode(GameState & gameState)
  {
    return (new DarkBombExplode(gameState));
  }

  AEntity*	EntityFactory::createFireBombExplode(GameState & gameState)
  {
    return (new FireBombExplode(gameState));
  }

  AEntity*	EntityFactory::createPowerBombExplode(GameState & gameState)
  {
    return (new PowerBombExplode(gameState));
  }

  AEntity*	EntityFactory::createWaterBombExplode(GameState & gameState)
  {
    return (new WaterBombExplode(gameState));;
  }
};
