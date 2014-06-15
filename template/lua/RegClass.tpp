//
// RegClass.tpp for bomberman in /home/bichon_b/rendu/cpp_bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Sun Jun 15 08:26:08 2014 bichon_b
// Last update Sun Jun 15 08:26:08 2014 bichon_b
//

template <typename T>
void	LuaBiche::RegClass<T>::registry(lua_State* lua, T* obj)
{
  const std::vector<typename ILuaHeir<T>::t_MethodPtr>&				stuff = obj->getMethodPtr();
  typename std::vector<typename ILuaHeir<T>::t_MethodPtr>::const_iterator	it;

  lua_newtable(lua);
  int	methods = lua_gettop(lua);

  luaL_newmetatable(lua, obj->getClassName().c_str());
  int	metatable = lua_gettop(lua);

  for (it = stuff.begin(); it != stuff.end(); it++)
    {
      lua_pushstring(lua, it->name.c_str());
      lua_pushlightuserdata(lua, (void*)&(*it));
      lua_pushcclosure(lua, trampoline, 1);
      lua_settable(lua, methods);
    }
  lua_pushstring(lua, "__index");
  lua_pushvalue(lua, methods);
  lua_settable(lua, metatable);

  lua_pushstring(lua, "__tostring");
  lua_pushcfunction(lua, tostring_T);
  lua_settable(lua, metatable);

  lua_setmetatable(lua, methods);
}

template <typename T>
void	LuaBiche::RegClass<T>::push(lua_State* lua, std::string const& name, T* obj)
{
  T	**tmp = static_cast<T**>(lua_newuserdata(lua, sizeof(T*)));
  *(tmp) = obj;
  luaL_setmetatable(lua, obj->getClassName().c_str());
  lua_setglobal(lua, name.c_str());
  lua_pop(lua, 1);
}

template <typename T>
int	LuaBiche::RegClass<T>::trampoline(lua_State* lua)
{
  T	**tmp = static_cast<T**>(lua_touserdata(lua, 1));
  T	*obj = *tmp;

  lua_remove(lua, 1);
  typename ILuaHeir<T>::t_MethodPtr	*stuff = static_cast<typename ILuaHeir<T>::t_MethodPtr*>(lua_touserdata(lua, lua_upvalueindex(1)));
  return (obj->*(stuff->methodPtr))(lua);
}

template <typename T>
int	LuaBiche::RegClass<T>::tostring_T(lua_State* L)
{
  T	**tmp = static_cast<T**>(lua_touserdata(L, 1));
  T	*obj = *tmp;

  std::cout << "affichage" << std::endl;
  lua_pushfstring(L, "%s", obj->getClassName().c_str());
  return (1);
}
