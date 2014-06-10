//
// ISerializable.hh for  in /home/pinon_a/rendu/cpp_bomberman/test/test/include
//
// Made by pinon
// Login   <pinon_a@epitech.net>
//
// Started on  Wed May 21 15:11:25 2014 pinon
// Last update Mon Jun  9 15:59:45 2014 pinon
//

#ifndef		ISERIALIZABLE_HH
# define	ISERIALIZABLE_HH

class ISerializedNode;

class ISerializable
{
public:
  virtual ~ISerializable () {};

  virtual void pack(ISerializedNode & current) const = 0;
  virtual void unpack(const ISerializedNode & current) = 0;
};

#endif
