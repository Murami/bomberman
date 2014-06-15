//
// BonusFactory.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:27 2014 quentin desabre
// Last update Sun Jun 15 08:33:28 2014 Desabre Quentin
//

#ifndef		_BONUSFACTORY_HH_
# define	_BONUSFACTORY_HH_

# include	<map>
# include	<glm/glm.hpp>
# include	"entity/Player.hh"

namespace bbm
{
  class AEntity;

  class BonusFactory
  {

  protected:
    BonusFactory();
    ~BonusFactory();

  public:
    typedef AEntity* (BonusFactory::*FactoryMethod)(const glm::vec2&);

    static BonusFactory*	getInstance();
    static void			delInstance();

    AEntity*			create(BonusType type, const glm::vec2 & pos);
    AEntity*			createRandom(const glm::vec2 & pos);
    AEntity*			createNone(const glm::vec2 & pos);
    AEntity*			createSpeedBonus(const glm::vec2 & pos);
    AEntity*			createBombBonus(const glm::vec2 & pos);
    AEntity*			createPowerBonus(const glm::vec2 & pos);
    AEntity*			createWaterBonus(const glm::vec2 & pos);
    AEntity*			createFireBonus(const glm::vec2 & pos);
    AEntity*			createDarkBonus(const glm::vec2 & pos);
    AEntity*			createBoxBonus(const glm::vec2 & pos);
    AEntity*			createRandomBonus(const glm::vec2 & pos);
    AEntity*			createMultiBombBonus(const glm::vec2 & pos);


  public:
    static BonusFactory*	       		_instance;
    static std::map<BonusType, FactoryMethod>	_map;
  };
};

#endif		/* BONUSFACTORY_HH_ */
