#include "events/InputConfig.hh"

namespace bbm
{
  InputConfig::InputConfig()
  {

  }

  InputConfig::~InputConfig()
  {

  }

  unsigned int	InputConfig::getKey(const std::string & key) const
  {
    return (_keyMap.at(key));
  }

  void		InputConfig::bindKey(const std::string & event, unsigned int key)
  {
    _keyMap[event] = key;
  }


  void		InputConfig::load(const std::string & file)
  {

  }

  void		InputConfig::save(const std::string & file)
  {

  }

  void		InputConfig::pack(ISerializedNode & current) const
  {

  }

  void		InputConfig::unpack(const ISerializedNode & current)
  {

  }

}
