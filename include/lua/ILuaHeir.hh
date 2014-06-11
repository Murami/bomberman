//
// ILuaHeir.hh for bomberman in /home/bichon_b/projets/bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Wed Jun  4 16:03:28 2014 bichon_b
// Last update Sat Jun  7 11:25:45 2014 bichon_b
//

#ifndef _ILUAHEIR_HH_
# define _ILUAHEIR_HH_

# include <lua.hpp>
# include <string>
# include <vector>

template <typename T>
class	ILuaHeir
{
  public:
  typedef struct MethodPtr
  {
    std::string	name;
    int		(T::*methodPtr)(lua_State*);
  }		t_MethodPtr;

public:
  ILuaHeir() {}
  ~ILuaHeir() {}

  virtual std::string					getClassName() const = 0;
  virtual const std::vector<ILuaHeir<T>::t_MethodPtr>&	getMethodPtr() const = 0;
};

#endif /*!_ILUAHEIR_HH_*/
