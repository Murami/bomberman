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
