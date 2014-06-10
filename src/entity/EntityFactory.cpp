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
};
