//
// EntityFactory.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:10 2014 quentin desabre
// Last update Sun Jun 15 08:33:10 2014 Desabre Quentin
//

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
    AEntity*	createPowerBomb(GameState & gameState);
    AEntity*	createWaterBomb(GameState & gameState);
    AEntity*	createFireBomb(GameState & gameState);
    AEntity*	createDarkBomb(GameState & gameState);
    AEntity*	createBoxBomb(GameState & gameState);
    AEntity*	createMultiBomb(GameState & gameState);
    AEntity*	createDarkBombExplode(GameState & gameState);
    AEntity*	createFireBombExplode(GameState & gameState);
    AEntity*	createPowerBombExplode(GameState & gameState);
    AEntity*	createWaterBombExplode(GameState & gameState);

  public:
    static std::map<std::string, FactoryMethod>	_map;
  };
};


#endif
