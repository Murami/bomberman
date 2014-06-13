//
// LuaBiche.cpp for bomberman in /home/bichon_b/projets/bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Tue May 20 12:22:22 2014 bichon_b
// Last update Fri Jun 13 02:18:53 2014 bichon_b
//

#include "lua/LuaBiche.hh"
#include <iostream>
#include <stdlib.h>

LuaBiche::LuaBiche(std::string const& file)
{
  _lua = luaL_newstate();
  luaL_openlibs(_lua);
  if (luaL_loadfile(_lua, file.c_str()))
    {
      std::cerr << lua_tostring(_lua, -1) << std::endl;
      throw ;
    }
}

LuaBiche::~LuaBiche()
{
  lua_close(_lua);
}

void	LuaBiche::run()
{
  if (lua_pcall(_lua, 0, LUA_MULTRET, 0))
    std::cerr << "Error in lua script : " << lua_tostring(_lua, -1) << std::endl;
}

void	LuaBiche::addVar(std::string const& name, std::string const& value)
{
  pushOnStack(value);
  lua_setglobal(_lua, name.c_str());
}

void	LuaBiche::addVar(std::string const& name, int value)
{
  pushOnStack(value);
  lua_setglobal(_lua, name.c_str());
}

void	LuaBiche::addVar(std::string const& name, bool value)
{
  pushOnStack(value);
  lua_setglobal(_lua, name.c_str());
}

void	LuaBiche::addVar(std::string const& name, double value)
{
  pushOnStack(value);
  lua_setglobal(_lua, name.c_str());
}

void	LuaBiche::pushOnStack(std::string const& value)
{
  lua_pushstring(_lua, value.c_str());
}

void	LuaBiche::pushOnStack(int value)
{
  lua_pushinteger(_lua, value);
}

void	LuaBiche::pushOnStack(bool value)
{
  lua_pushboolean(_lua, value);
}

void	LuaBiche::pushOnStack(double value)
{
  lua_pushnumber(_lua, value);
}

struct str {
  int	i;
  int	getI()
  {
    return (i);
  }
};
