//
// LuaBiche.tpp for bomberman in /home/bichon_b/rendu/cpp_bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Sun Jun 15 08:25:56 2014 bichon_b
// Last update Sun Jun 15 08:25:56 2014 bichon_b
//

template <typename T>
void	LuaBiche::addVar(std::string const& name, T begin, T const& end)
{
  int	i = 1;

  lua_newtable(_lua);
  for (; begin != end; begin++)
    {
      pushContainer(begin, i);
      lua_rawset(_lua, -3);
      i++;
    }
  lua_setglobal(_lua, name.c_str());
}

template <typename T>
void	LuaBiche::pushContainer(T it, int i)
{
  pushOnStack(i);
  pushOnStack(*it);
}

template <typename U, typename V>
void	LuaBiche::pushContainer(std::pair<U, V> pair, int)
{
  pushOnStack(pair.first);
  pushOnStack(pair.second);
}

template <typename T>
void	LuaBiche::addObject(std::string const& name, T *object)
{
  luaL_getmetatable(_lua, object->getClassName().c_str());
  if (lua_isnil(_lua, -1))
    {
      lua_pop(_lua, 1);
      LuaBiche::RegClass<T>::registry(_lua, object);
    }
  LuaBiche::RegClass<T>::push(_lua, name, object);
}
