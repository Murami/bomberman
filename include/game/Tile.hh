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
	Box = 1,
	Wall
      } TileType;

  public:
    Tile();
    Tile(IDrawable* drawable, bool collide);
    Tile(const Tile& tile);
    ~Tile();

    Tile&		operator=(const Tile& tile);
    bool		getCollide();
    const std::string&	getTexture();
    const std::string&	getShader();
    TileType		getType();

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
