#include <iostream>
#include <sstream>
#include <algorithm>

#include "game/TileMap.hh"
#include "game/Tile.hh"
#include "game/Wall.hh"
#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "graphic/TextureManager.hh"
#include "graphic/ShaderManager.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"

namespace bbm
{
  TileMap::TileMap()
  {
  }

  TileMap::TileMap(const glm::ivec2& size)
  {
    // _size = size;
    // _tiles.resize(_size.x * size.y, NULL);
    // _object.setPrimitive(GL_QUADS);
    // _object.setShader("default");
    // _object.setTexture("fire");


    // _object.pushVertex(glm::vec3(0, 0, 0));
    // _object.pushVertex(glm::vec3(20, 0, 0));
    // _object.pushVertex(glm::vec3(20, 20, 0));
    // _object.pushVertex(glm::vec3(0, 20, 0));
    // _object.pushUv(glm::vec2(0, 0));
    // _object.pushUv(glm::vec2(1, 0));
    // _object.pushUv(glm::vec2(1, 1));
    // _object.pushUv(glm::vec2(0, 1));
    // _object.build();
  }

  TileMap::~TileMap()
  {
  }


  void	TileMap::load(const std::string & file)
  {
    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->deserializeFromFile(file, *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Deserializer TileMap Error : " + std::string(ex.what()));

      }

    _object.pushVertex(glm::vec3(0, 0, 0));
    _object.pushVertex(glm::vec3(20, 0, 0));
    _object.pushVertex(glm::vec3(20, 20, 0));
    _object.pushVertex(glm::vec3(0, 20, 0));
    _object.pushUv(glm::vec2(0, 0));
    _object.pushUv(glm::vec2(1, 0));
    _object.pushUv(glm::vec2(1, 1));
    _object.pushUv(glm::vec2(0, 1));
    _object.build();
  }

  void	TileMap::save(const std::string & file)
  {

    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->serializeToFile(file, *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Serializer TileMap Error : " + std::string(ex.what()));
      }
  }


  void	TileMap::pack(ISerializedNode & current) const
  {
    std::vector<Tile*>::const_iterator	it;
    ISerializedNode*			vectorNode;
    ISerializedNode*			tileNode;
    int					index;
    int					i;

    current.add("size", _size);
    current.add("spawns", _spawns);
    current.add("ground", _object);
    vectorNode = current.add("tiles");
    for (i = 0, it = _tiles.begin(); it != _tiles.end(); ++it)
      {
	if (*it != NULL)
	  {
	    std::stringstream	ss;

	    index = std::distance(_tiles.begin(),
				  std::find(_tiles.begin(),
					    _tiles.end(), *it));
	    ss << i;
	    tileNode = vectorNode->add(ss.str());
	    tileNode->add("x", index % _size.x);
	    tileNode->add("y", index / _size.x);
	    tileNode->add("object", *(*it));
	    i++;
	  }
      }
  }

  void	TileMap::unpack(const ISerializedNode & current)
  {
    int				size;
    int				index;
    int				x;
    int				y;
    ISerializedNode*		vectorNode;
    ISerializedNode*		tileNode;

    current.get("size", _size);
    current.get("spawns", _spawns);
    current.get("ground", _object);
    _tiles.resize(_size.x * _size.y, NULL);
    vectorNode = current.get("tiles");
    size = vectorNode->size();
    for (index = 0; index < size; index++)
      {
    	std::stringstream	ss;
	Tile*			tile = new Tile;

    	ss << index;
	tileNode = vectorNode->get(ss.str());
	tileNode->get("x", x);
	tileNode->get("y", y);
	tileNode->get("object", *tile);
	tile->setDrawable(new Wall(tile->getTexture(), tile->getShader()));
	setTile(x, y, tile);
      }
  }

  bool		TileMap::collide(int x, int y)
  {
    if (x >= _size.x || x < 0 || y < 0 || y >= _size.y)
      throw (std::runtime_error("out of bounds"));

    Tile*	tile = _tiles[x + y * _size.x];
    if (tile)
      return (tile->getCollide());
    return (false);
  }

  glm::ivec2	TileMap::getSize()
  {
    return (_size);
  }

  void		TileMap::setTile(int x, int y, Tile* tile)
  {
    if (x >= _size.x || x < 0 || y < 0 || y >= _size.y)
      throw (std::runtime_error("out of bounds"));
    _tiles[x + y * _size.x] = tile;
  }

  Tile*		TileMap::getTile(int x, int y)
  {
    if (x >= _size.x || x < 0 || y < 0 || y >= _size.y)
      throw (std::runtime_error("out of bounds"));
    return (_tiles[x + y * _size.x]);
  }

  void		TileMap::draw(ARenderer& renderer, const RenderState& renderState)
  {
    RenderState	newState = renderState;
    Transform	transform = renderState.transform;

    for (int y = 0; y < _size.y; y++)
      {
	for (int x = 0; x < _size.x; x++)
	  {
	    Tile*	tile;

	    tile = getTile(x, y);
	    if (tile)
	      {
		newState.transform = transform;
		newState.transform.translate(glm::vec3(x, y, 0));
		renderer.draw(*tile, newState);
	      }
	  }
      }
    renderer.draw(_object, renderState);
  }
};
