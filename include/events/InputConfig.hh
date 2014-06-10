#ifndef		_INPUT_CONFIG_HH_
# define	_INPUT_CONFIG_HH_

# include	<iostream>
# include	<map>
# include	"serializer/ISerializable.hh"

namespace bbm
{
  class InputConfig : public ISerializable
  {
  public:
    InputConfig();
    ~InputConfig();

  public:
    unsigned int	getKey(const std::string &) const;
    void		bindKey(const std::string & event, unsigned int key);
    void		load(const std::string & file);
    void		save(const std::string & file);
    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);

  private:
    std::map<std::string, unsigned int>	_keyMap;
  };
};

#endif		/* _INPUT_CONFIG_HH_ */
