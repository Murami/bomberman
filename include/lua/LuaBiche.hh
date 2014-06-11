
#ifndef _LUABICHE_HH_
# define _LUABICHE_HH_

# include <iostream>
# include <lua.hpp>
# include <map>
# include "ILuaHeir.hh"

class	LuaBiche
{

  /* nested class pour enregistrer les object en lua */
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

  virtual void	run();

  virtual void	addVar(std::string const& name, std::string const& value);
  virtual void	addVar(std::string const& name, bool value);
  virtual void	addVar(std::string const& name, int value);
  virtual void	addVar(std::string const& name, double value);

  template <typename T>
  void	addVar(std::string const& name, T begin, T const& end);

  // void	addObject(std::string const& name, ILuaObject *object);
  template <typename T>
  void	addObject(std::string const& name, T *object);

  static void	*pushuserdata(lua_State*, void*, size_t);
  template <typename T>
  static int	push(lua_State*, ILuaHeir<T>*);
  static int	new_T(lua_State*);

  static int	thunk(lua_State *)
  {
    std::cout << "enter" << std::endl;
    return (0);
  }

private:
  /* on pousse sur la stack des données de différents types pour y avoir accès en Lua */
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

/* implementation des methodes templates */
# include "template/LuaBiche.tpp"
# include "template/RegClass.tpp"

#endif /*!_LUABICHE_HH_*/
