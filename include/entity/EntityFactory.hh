#ifndef		ENTITY_FACTORY_HH
# define	ENTITY_FACTORY_HH

#include <string>
#include <map>

namespace bbm
{
  class AEntity;
  class GameState;

  class EntityFactory
  {
  public:
    EntityFactory();
    ~EntityFactory();

    typedef AEntity* (EntityFactory::*FactoryMethod)(GameState & gameState);

    AEntity*	create(const std::string& type, GameState & gameState);
    AEntity*	createRandom(GameState & gameState);
    AEntity*	createNone(GameState & gameState);
    AEntity*	createSpeedBonus(GameState & gameState);
    AEntity*	createBombBonus(GameState & gameState);
    AEntity*	createPowerBonus(GameState & gameState);
    AEntity*	createWaterBonus(GameState & gameState);
    AEntity*	createFireBonus(GameState & gameState);
    AEntity*	createDarkBonus(GameState & gameState);
    AEntity*	createBoxBonus(GameState & gameState);
    AEntity*	createRandomBonus(GameState & gameState);
    AEntity*	createMultiBombBonus(GameState & gameState);
    AEntity*	createGameBox(GameState & gameState);

  public:
    static std::map<std::string, FactoryMethod>	_map;
  };
};


#endif
