//
// AEntity.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:30:06 2014 quentin desabre
// Last update Sun Jun 15 11:04:04 2014 bichon_b
//

#include "entity/AEntity.hh"
#include "serializer/ISerializedNode.hh"

namespace bbm
{
  const float collidDelta = 0.01;

  unsigned int	AEntity::_lastInstanceID = 1;

  AEntity::AEntity()
  {
    _idPlayer = 0;
    _id = newID();
  }

  AEntity::~AEntity()
  {
  }

  unsigned int	AEntity::getID() const
  {
    return (_id);
  }

  void		AEntity::setID(unsigned int id)
  {
    _id = id;
  }

  unsigned int	AEntity::getLastID() const
  {
    return (_lastInstanceID);
  }

  void		AEntity::setLastID(unsigned int id)
  {
    _lastInstanceID = id;
  }

  unsigned int	AEntity::newID()
  {
    return (_lastInstanceID++);
  }

  void          AEntity::pack(ISerializedNode & current) const
  {
    int	id;
    int lastId;

    id = getID();
    lastId = getLastID();
    current.add("type", _type);
    current.add("position", _pos);
    current.add("idPlayer", _idPlayer);
    current.add("id", id);
    current.add("lastId", lastId);
  }

  void	        AEntity::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    current.get("idPlayer", _idPlayer);
    current.get("id", _id);
    current.get("lastId", _lastInstanceID);
  }

  unsigned int	AEntity::getIDPlayer() const
  {
    return (_idPlayer);
  }
};
