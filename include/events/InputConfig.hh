//
// InputConfig.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:38:33 2014 otoshigami
// Last update Sun Jun 15 08:38:34 2014 otoshigami
//

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

    typedef struct	s_data
    {
      int		key;
      std::string	keyName;
    }			t_data;

    static const std::map<std::string, int> SDLKeyMap;

  public:
    unsigned int	getKey(const std::string &) const;
    const std::string&  getKeyName(const std::string & key) const;
    void		bindKey(const std::string & event,
				const std::string & key);

    void		load(const std::string & file);
    void		save(const std::string & file);
    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);

  private:
    std::map<std::string, t_data>	_keyMap;
  };
};

#endif		/* _INPUT_CONFIG_HH_ */
