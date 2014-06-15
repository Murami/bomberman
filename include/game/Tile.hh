//
// Tile.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:37:07 2014 otoshigami
// Last update Sun Jun 15 08:37:08 2014 otoshigami
//

#ifndef TILE_HH
#define TILE_HH

#include <string>
#include "graphic/IDrawable.hh"
#include "serializer/ISerializable.hh"

class ISerializedNode;

namespace bbm
{
  class	ARenderer;
  class RenderState;

  class	Tile : public IDrawable, public ISerializable
  {
  public:

    typedef enum TileType
      {
	Void = 0,
	Box = 1,
	Wall = 2,
	Spawn = 3
      } TileType;

  public:
    Tile();
    Tile(bool collide, const std::string & texture,
	 const std::string & shader, TileType type);
    Tile(IDrawable* drawable, bool collide);
    Tile(const Tile& tile);
    ~Tile();

    Tile&		operator=(const Tile& tile);
    bool		getCollide();
    const std::string&	getTexture();
    const std::string&	getShader();
    TileType		getType();
    IDrawable*		getDrawable();

    void		setDrawable(IDrawable* drawable);

    void		pack(ISerializedNode & current) const;
    void		unpack(const ISerializedNode & current);

  protected:
    void		draw(ARenderer& renderer, const RenderState& renderState);

  private:
    IDrawable*	_drawable;
    bool	_collide;
    TileType	_type;
    std::string _texture;
    std::string _shader;
  };
};

#endif /* TILE_HH */
