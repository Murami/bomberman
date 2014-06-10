#ifndef TILEMANAGER_HH
#define TILEMANAGER_HH

#include <string>
#include <map>

namespace bbm
{
  class	IDrawable;

  class	TileManager
  {
  private:
    TileManager();
    ~TileManager();

    typedef	std::map<std::string, IDrawable*>::iterator		DrawableListIt;
    typedef	std::map<std::string, IDrawable*>::const_iterator	ConstDrawableListIt;

  public:
    void	addTile(const std::string& name, IDrawable* drawable);
    void	delTile(const std::string& name);
    IDrawable*	getTile(const std::string& name) const;


    static TileManager*	getInstance();
    static void		deleteInstance();

  private:
    std::map<std::string, IDrawable*>	_drawables;
    static TileManager*			_instance;
  };
};

#endif /* TILEMANAGER_HH */
