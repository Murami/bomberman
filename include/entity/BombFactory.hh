#ifndef		_BOMBFACTORY_HH_
# define	_BOMBFACTORY_HH_

# include	<map>
# include	<glm/glm.hpp>
# include	"entity/Player.hh"

namespace bbm
{
  class AEntity;

  class BombFactory
  {

  protected:
    BombFactory();
    ~BombFactory();

  public:
    typedef AEntity* (BombFactory::*FactoryMethod)(const glm::vec2&,
						   GameState&,
						   unsigned int);

    static BombFactory*				getInstance();
    static void					delInstance();

    AEntity*					create(BombType type, const glm::vec2 & pos,
						       GameState& , unsigned int);
    AEntity*					createRandom(const glm::vec2 &,
							     GameState&, unsigned int);
    AEntity*					createPowerBomb(const glm::vec2 &,
								GameState&, unsigned int);
    AEntity*					createWaterBomb(const glm::vec2 &,
								GameState&, unsigned int);
    AEntity*					createFireBomb(const glm::vec2 &,
							       GameState&, unsigned int);
    AEntity*					createDarkBomb(const glm::vec2 &,
							       GameState&, unsigned int);
    AEntity*					createBoxBomb(const glm::vec2 &,
							      GameState&, unsigned int);
    AEntity*					createMultiBomb(const glm::vec2 &,
								GameState&,  unsigned int);


  public:
    static BombFactory*				_instance;
    static std::map<BombType, FactoryMethod>	_map;
  };
};

#endif		/* BOMBFACTORY_HH_ */
