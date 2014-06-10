#ifndef TILEMAP_HH
#define TILEMAP_HH

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "graphic/IDrawable.hh"
#include "graphic/Object.hh"
#include "serializer/ISerializable.hh"
#include "serializer/SerializableVector.hh"

class ISerializedNode;

namespace bbm
{
  class	ARenderer;
  class	RenderState;
  class	Tile;

  class	TileMap : public IDrawable, public ISerializable
  {
  public:
    TileMap(const std::string& file);
    ~TileMap();

    bool	collide(int x, int y);

    glm::ivec2	getSize();
    void	setTile(int x, int y, Tile* tile);
    Tile*	getTile(int x, int y);

    void	pack(ISerializedNode & current) const;
    void	unpack(const ISerializedNode & current);

  protected:
    void	draw(ARenderer& renderer, const RenderState& renderState);

  private:
    std::vector<Tile*>			_tiles;
    SerializableVector<glm::ivec2>	_spawns;
    glm::ivec2				_size;
    Object				_object;
  };
};

#endif /* TILEMAP_HH */
