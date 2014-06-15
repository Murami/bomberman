//
// BonusFactory.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:29:35 2014 quentin desabre
// Last update Sun Jun 15 08:29:36 2014 Desabre Quentin
//

#include <cstdlib>
#include "entity/BonusFactory.hh"
#include "entity/AEntity.hh"
#include "entity/FireBonus.hh"
#include "entity/BoxBonus.hh"
#include "entity/BombBonus.hh"
#include "entity/MultiBombBonus.hh"
#include "entity/RandomBonus.hh"
#include "entity/PowerBonus.hh"
#include "entity/SpeedBonus.hh"
#include "entity/DarkBonus.hh"
#include "entity/WaterBonus.hh"

namespace bbm
{
  std::map<BonusType, BonusFactory::FactoryMethod>	create_map()
  {
    std::map<BonusType, BonusFactory::FactoryMethod>	map;

    map[NONE] = &BonusFactory::createNone;
    map[BOX_BONUS] = &BonusFactory::createBoxBonus;
    map[SPEED_BONUS] = &BonusFactory::createSpeedBonus;
    map[BOMB_BONUS] = &BonusFactory::createBombBonus;
    map[FIRE_BONUS] = &BonusFactory::createFireBonus;
    map[WATER_BONUS] = &BonusFactory::createWaterBonus;
    map[RANDOM_BONUS] = &BonusFactory::createRandomBonus;
    map[MULTIBOMB_BONUS] = &BonusFactory::createMultiBombBonus;
    map[DARK_BONUS] = &BonusFactory::createDarkBonus;
    map[POWER_BONUS] = &BonusFactory::createPowerBonus;

    return (map);
  }

  std::map<BonusType, BonusFactory::FactoryMethod>	BonusFactory::_map = create_map();
  BonusFactory *					BonusFactory::_instance = NULL;


  BonusFactory::BonusFactory()
  {
  }

  BonusFactory::~BonusFactory()
  {
  }

  BonusFactory*		BonusFactory::getInstance()
  {
    if (_instance == NULL)
      _instance = new BonusFactory();
    return (_instance);
  }

  void			BonusFactory::delInstance()
  {
    if (_instance != NULL)
      {
	_instance = NULL;
	delete (_instance);
      }
  }

  AEntity*	       	BonusFactory::create(BonusType type, const glm::vec2 & pos)
  {
    return ((this->*_map[type])(pos));
  }

  AEntity*	       	BonusFactory::createRandom(const glm::vec2 & pos)
  {

    return ((this->*_map[static_cast<BonusType>(std::rand() % _map.size())])(pos));
  }

  AEntity*		BonusFactory::createNone(const glm::vec2 & pos)
  {
    (void)pos;
    return (NULL);
  }

  AEntity*		BonusFactory::createSpeedBonus(const glm::vec2 & pos)
  {
    return (new SpeedBonus(pos));
  }

  AEntity*		BonusFactory::createBombBonus(const glm::vec2 & pos)
  {
    return (new BombBonus(pos));
  }

  AEntity*		BonusFactory::createPowerBonus(const glm::vec2 & pos)
  {
    return (new PowerBonus(pos));
  }

  AEntity*		BonusFactory::createWaterBonus(const glm::vec2 & pos)
  {
    return (new WaterBonus(pos));
  }

  AEntity*		BonusFactory::createFireBonus(const glm::vec2 & pos)
  {
    return (new FireBonus(pos));
  }

  AEntity*		BonusFactory::createDarkBonus(const glm::vec2 & pos)
  {
    return (new DarkBonus(pos));
  }

  AEntity*		BonusFactory::createBoxBonus(const glm::vec2 & pos)
  {
    return (new BoxBonus(pos));
  }

  AEntity*		BonusFactory::createRandomBonus(const glm::vec2 & pos)
  {
    return (new RandomBonus(pos));
  }

  AEntity*		BonusFactory::createMultiBombBonus(const glm::vec2 & pos)
  {
    return (new MultiBombBonus(pos));
  }
}
