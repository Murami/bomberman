//
// TileMap.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:38:02 2014 otoshigami
// Last update Sun Jun 15 12:56:05 2014 otoshigami
//

#ifndef TILEMAP_HH
#define TILEMAP_HH

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "game/Tile.hh"

#include "graphic/IDrawable.hh"
#include "graphic/Object.hh"

#include "serializer/ISerializable.hh"
#include "serializer/SerializableVector.hh"

class ISerializedNode;

namespace bbm
{
  class	ARenderer;
  class	RenderState;

  class	TileMap : public ISerializable
  {
  public:
    TileMap();
    ~TileMap();

    bool				collide(int x, int y);

    glm::ivec2				getSize();
    void				setTile(int x, int y, Tile* tile);
    Tile*				getTile(int x, int y);
    Tile::TileType			getTileType(int x, int y);
    SerializableVector<glm::ivec2>&	getSpawns();

    void				pack(ISerializedNode & current) const;
    void				unpack(const ISerializedNode & current);
    void				load(const std::string & file);
    void				save(const std::string & file);
    void				randomize(int x, int y);
    void				draw(ARenderer& renderer,
					     const RenderState& renderState,
					     const glm::vec2& position);

  private:
    std::vector<Tile*>			_tiles;
    SerializableVector<glm::ivec2>	_spawns;
    glm::ivec2				_size;
    Object				_object;
  };
};

#endif /* TILEMAP_HH */
