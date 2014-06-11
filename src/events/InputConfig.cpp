#include <SDL.h>
#include <sstream>
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"
#include "events/InputConfig.hh"

namespace bbm
{
  std::map<std::string, int> create_SDLKeyMap()
  {
    std::map<std::string, int> m;
    m["SDLK_UNKNOWN"] = SDLK_UNKNOWN;
    m["SDLK_BACKSPACE"] = SDLK_BACKSPACE;
    m["SDLK_TAB"] = SDLK_TAB;
    m["SDLK_CLEAR"] = SDLK_CLEAR;
    m["SDLK_RETURN"] = SDLK_RETURN;
    m["SDLK_PAUSE"] = SDLK_PAUSE;
    m["SDLK_ESCAPE"] = SDLK_ESCAPE;
    m["SDLK_SPACE"] = SDLK_SPACE;
    m["SDLK_EXCLAIM"] = SDLK_EXCLAIM;
    m["SDLK_QUOTEDBL"] = SDLK_QUOTEDBL;
    m["SDLK_HASH"] = SDLK_HASH;
    m["SDLK_DOLLAR"] = SDLK_DOLLAR;
    m["SDLK_AMPERSAND"] = SDLK_AMPERSAND;
    m["SDLK_QUOTE"] = SDLK_QUOTE;
    m["SDLK_LEFTPAREN"] = SDLK_LEFTPAREN;
    m["SDLK_RIGHTPAREN"] = SDLK_RIGHTPAREN;
    m["SDLK_ASTERISK"] = SDLK_ASTERISK;
    m["SDLK_PLUS"] = SDLK_PLUS;
    m["SDLK_COMMA"] = SDLK_COMMA;
    m["SDLK_MINUS"] = SDLK_MINUS;
    m["SDLK_PERIOD"] = SDLK_PERIOD;
    m["SDLK_SLASH"] = SDLK_SLASH;
    m["SDLK_0"] = SDLK_0;
    m["SDLK_1"] = SDLK_1;
    m["SDLK_2"] = SDLK_2;
    m["SDLK_3"] = SDLK_3;
    m["SDLK_4"] = SDLK_4;
    m["SDLK_5"] = SDLK_5;
    m["SDLK_6"] = SDLK_6;
    m["SDLK_7"] = SDLK_7;
    m["SDLK_8"] = SDLK_8;
    m["SDLK_9"] = SDLK_9;
    m["SDLK_COLON"] = SDLK_COLON;
    m["SDLK_SEMICOLON"] = SDLK_SEMICOLON;
    m["SDLK_LESS"] = SDLK_LESS;
    m["SDLK_EQUALS"] = SDLK_EQUALS;
    m["SDLK_GREATER"] = SDLK_GREATER;
    m["SDLK_QUESTION"] = SDLK_QUESTION;
    m["SDLK_AT"] = SDLK_AT;
    m["SDLK_LEFTBRACKET"] = SDLK_LEFTBRACKET;
    m["SDLK_BACKSLASH"] = SDLK_BACKSLASH;
    m["SDLK_RIGHTBRACKET"]	= SDLK_RIGHTBRACKET;
    m["SDLK_CARET"] = SDLK_CARET;
    m["SDLK_UNDERSCORE"] = SDLK_UNDERSCORE;
    m["SDLK_BACKQUOTE"] = SDLK_BACKQUOTE;
    m["SDLK_a"] = SDLK_a;
    m["SDLK_b"] = SDLK_b;
    m["SDLK_c"] = SDLK_c;
    m["SDLK_d"] = SDLK_d;
    m["SDLK_e"] = SDLK_e;
    m["SDLK_f"] = SDLK_f;
    m["SDLK_g"] = SDLK_g;
    m["SDLK_h"] = SDLK_h;
    m["SDLK_i"] = SDLK_i;
    m["SDLK_j"] = SDLK_j;
    m["SDLK_k"] = SDLK_k;
    m["SDLK_l"] = SDLK_l;
    m["SDLK_m"] = SDLK_m;
    m["SDLK_n"] = SDLK_n;
    m["SDLK_o"] = SDLK_o;
    m["SDLK_p"] = SDLK_p;
    m["SDLK_q"] = SDLK_q;
    m["SDLK_r"] = SDLK_r;
    m["SDLK_s"] = SDLK_s;
    m["SDLK_t"] = SDLK_t;
    m["SDLK_u"] = SDLK_u;
    m["SDLK_v"] = SDLK_v;
    m["SDLK_w"] = SDLK_w;
    m["SDLK_x"] = SDLK_x;
    m["SDLK_y"] = SDLK_y;
    m["SDLK_z"] = SDLK_z;
    m["SDLK_DELETE"] = SDLK_DELETE;
    m["SDLK_KP_0"] = SDLK_KP_0;
    m["SDLK_KP_1"] = SDLK_KP_1;
    m["SDLK_KP_2"] = SDLK_KP_2;
    m["SDLK_KP_3"] = SDLK_KP_3;
    m["SDLK_KP_4"] = SDLK_KP_4;
    m["SDLK_KP_5"] = SDLK_KP_5;
    m["SDLK_KP_6"] = SDLK_KP_6;
    m["SDLK_KP_7"] = SDLK_KP_7;
    m["SDLK_KP_8"] = SDLK_KP_8;
    m["SDLK_KP_9"] = SDLK_KP_9;
    m["SDLK_KP_PERIOD"] = SDLK_KP_PERIOD;
    m["SDLK_KP_DIVIDE"] = SDLK_KP_DIVIDE;
    m["SDLK_KP_MULTIPLY"] = SDLK_KP_MULTIPLY;
    m["SDLK_KP_MINUS"] = SDLK_KP_MINUS;
    m["SDLK_KP_PLUS"] = SDLK_KP_PLUS;
    m["SDLK_KP_ENTER"] = SDLK_KP_ENTER;
    m["SDLK_KP_EQUALS"] = SDLK_KP_EQUALS;
    m["SDLK_UP"] = SDLK_UP;
    m["SDLK_DOWN"] = SDLK_DOWN;
    m["SDLK_RIGHT"] = SDLK_RIGHT;
    m["SDLK_LEFT"] = SDLK_LEFT;
    m["SDLK_INSERT"] = SDLK_INSERT;
    m["SDLK_HOME"] = SDLK_HOME;
    m["SDLK_END"] = SDLK_END;
    m["SDLK_PAGEUP"] = SDLK_PAGEUP;
    m["SDLK_PAGEDOWN"] = SDLK_PAGEDOWN;
    m["SDLK_F1"] = SDLK_F1;
    m["SDLK_F2"] = SDLK_F2;
    m["SDLK_F3"] = SDLK_F3;
    m["SDLK_F4"] = SDLK_F4;
    m["SDLK_F5"] = SDLK_F5;
    m["SDLK_F6"] = SDLK_F6;
    m["SDLK_F7"] = SDLK_F7;
    m["SDLK_F8"] = SDLK_F8;
    m["SDLK_F9"] = SDLK_F9;
    m["SDLK_F10"] = SDLK_F10;
    m["SDLK_F11"] = SDLK_F11;
    m["SDLK_F12"] = SDLK_F12;
    m["SDLK_F13"] = SDLK_F13;
    m["SDLK_F14"] = SDLK_F14;
    m["SDLK_F15"] = SDLK_F15;
    m["SDLK_CAPSLOCK"] = SDLK_CAPSLOCK;
    m["SDLK_RSHIFT"] = SDLK_RSHIFT;
    m["SDLK_LSHIFT"] = SDLK_LSHIFT;
    m["SDLK_RCTRL"] = SDLK_RCTRL;
    m["SDLK_LCTRL"] = SDLK_LCTRL;
    m["SDLK_RALT"] = SDLK_RALT;
    m["SDLK_LALT"] = SDLK_LALT;
    m["SDLK_MODE"] = SDLK_MODE;
    m["SDLK_HELP"] = SDLK_HELP;
    m["SDLK_SYSREQ"] = SDLK_SYSREQ;
    m["SDLK_MENU"] = SDLK_MENU;
    m["SDLK_POWER"] = SDLK_POWER;
    m["SDLK_UNDO"] = SDLK_UNDO;
    return m;
  }

  std::map<std::string, int> const InputConfig::SDLKeyMap = create_SDLKeyMap();

  InputConfig::InputConfig()
  {

  }

  InputConfig::~InputConfig()
  {

  }

  void		InputConfig::load(const std::string & file)
  {
    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->deserializeFromFile(file, *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Deserializer InputConfig Error : " + std::string(ex.what()));
      }
  }

  void		InputConfig::save(const std::string & file)
  {
    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->serializeToFile(file, *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Deserializer InputConfig Error : " + std::string(ex.what()));
      }
  }

  void		InputConfig::pack(ISerializedNode & current) const
  {
    std::map<std::string, t_data>::const_iterator	it;
    ISerializedNode*					inputMapNode;
    ISerializedNode*					inputNode;
    int							i;

    inputMapNode = current.add("input");
    for (i = 0, it = _keyMap.begin(); it != _keyMap.end(); ++it, i++)
      {
	std::stringstream	ss;

	ss << i;
	inputNode = inputMapNode->add(ss.str());
	inputNode->add("action", it->first);
	inputNode->add("key", (it->second).keyName);
      }
  }

  void		InputConfig::unpack(const ISerializedNode & current)
  {
    ISerializedNode*	inputMapNode;
    ISerializedNode*	inputNode;
    int			size;
    int			index;
    std::string		action;
    std::string		key;

    inputMapNode = current.get("input");
    size = inputMapNode->size();
    for (index = 0; index < size; index++)
      {
    	std::stringstream	ss;

    	ss << index;
	inputNode = inputMapNode->get(ss.str());
	inputNode->get("action", action);
	inputNode->get("key", key);
	this->bindKey(action, key);
      }
  }

  unsigned int	InputConfig::getKey(const std::string & key) const
  {
    return (_keyMap.at(key).key);
  }

  const std::string&	InputConfig::getKeyName(const std::string & key) const
  {
    return (_keyMap.at(key).keyName);
  }

  void		InputConfig::bindKey(const std::string & event, const std::string& key)
  {
    t_data data;

    if (SDLKeyMap.find(key) == SDLKeyMap.end())
      throw SerializerException("input key [" + key + "] doesn't exist");
    data.key = SDLKeyMap.at(key);
    data.keyName = key;
    _keyMap[event] = data;
  }
}
