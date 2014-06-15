//
// LuaBiche.hh for bomberman in /home/bichon_b/rendu/cpp_bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Sun Jun 15 08:25:46 2014 bichon_b
// Last update Sun Jun 15 13:13:46 2014 otoshigami
//

#ifndef _LUABICHE_HH_
# define _LUABICHE_HH_

# include <iostream>
# include <lua.hpp>
# include <map>
# include "ILuaHeir.hh"

class	LuaBiche
{
  template <typename T>
  class RegClass
  {
    typedef struct { T *ptr; } userdataType;

  public:
    RegClass();
    ~RegClass();

    static void	registry(lua_State*, T*);
    static void	push(lua_State*, std::string const&, T*);
    static int	trampoline(lua_State*);
    static int	tostring_T(lua_State*);
  };

public:
  LuaBiche(std::string const& file);
  virtual ~LuaBiche();

  void	run();

  void	addVar(std::string const& name, std::string const& value);
  void	addVar(std::string const& name, bool value);
  void	addVar(std::string const& name, int value);
  void	addVar(std::string const& name, double value);

  template <typename T>
  void	addVar(std::string const& name, T begin, T const& end);

  template <typename T>
  void	addObject(std::string const& name, T *object);

  static void	*pushuserdata(lua_State*, void*, size_t);
  template <typename T>
  static int	push(lua_State*, ILuaHeir<T>*);

private:
  void	pushOnStack(std::string const& value);
  void	pushOnStack(bool  value);
  void	pushOnStack(int value);
  void	pushOnStack(double value);
  template <typename T>
  void	pushContainer(T it, int i);
  template <typename U, typename V>
  void	pushContainer(std::pair<U, V>, int);

private:
  lua_State	*_lua;
};

# include "lua/LuaBiche.tpp"
# include "lua/RegClass.tpp"

#endif /*!_LUABICHE_HH_*/
