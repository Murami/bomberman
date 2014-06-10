#include "entity/AEntity.hh"

namespace bbm
{
  const float collidDelta = 0.01;

  unsigned int	AEntity::_lastInstanceID = 0;

  AEntity::AEntity()
  {
    _id = newID();
  }

  AEntity::~AEntity()
  {
  }

  unsigned int	AEntity::getID()
  {
    return (_id);
  }

  unsigned int	AEntity::newID()
  {
    return (_lastInstanceID++);
  }
};
