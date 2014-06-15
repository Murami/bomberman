//
// TileMap.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:29:30 2014 otoshigami
// Last update Sun Jun 15 13:36:29 2014 otoshigami
//

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

  TileMap::~TileMap()
  {
  }

  void	TileMap::randomize(int x, int y)
  {

    Tile*	tile;
    int		i;
    int		posx;
    int		posy;
    bool	valid;

    _size = glm::ivec2(x, y);
    _tiles.resize(_size.x * _size.y, NULL);
    _object.initialize("ground", "default2", "GL_QUADS");
    _object.pushVertex(glm::vec3(0, 0, 0));
    _object.pushVertex(glm::vec3(x, 0, 0));
    _object.pushVertex(glm::vec3(x, y, 0));
    _object.pushVertex(glm::vec3(0, y, 0));
    _object.pushUv(glm::vec2(0, 0));
    _object.pushUv(glm::vec2(x, 0));
    _object.pushUv(glm::vec2(x, y));
    _object.pushUv(glm::vec2(0, y));
    _object.build();

    for (posx = 0; posx < x; posx++)
      {
	for (posy = 0; posy < y; posy++)
	  {
	    if (posx == 0 || posy == 0 || posx == x - 1 || posy == y - 1
		|| (posx % 2 == 0 && posy % 2 == 0))
	      {
		tile = new Tile(true, "wall", "default", Tile::Wall);
		tile->setDrawable(new Wall(tile->getTexture(), tile->getShader()));
		setTile(posx, posy, tile);
	      }
	  }
      }

    for (i = 0; i < (x * y) * 0.05; i++)
      {
	valid = false;
	while (valid == false)
	  {
	    posx = (std::rand() % (x - 2)) + 1;
	    posy = (std::rand() % (y - 2)) + 1;
	    if (getTileType(posx, posy) == Tile::Void &&
		getTileType(posx + 1, posy) != Tile::Wall &&
		getTileType(posx - 1, posy) != Tile::Wall &&
		getTileType(posx, posy + 1) != Tile::Wall &&
		getTileType(posx, posy - 1) != Tile::Wall)
	      {
		tile = new Tile(false, "", "", Tile::Spawn);
		tile->setDrawable(NULL);
		_spawns.push_back(glm::ivec2(posx, posy));
		setTile(posx, posy, tile);
		valid = true;
	      }
	  }
      }
  }

  void	TileMap::load(const std::string & file)
  {
    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->deserializeFromFile("maps/" + file + ".map", *this);
      }
    catch (SerializerException& ex)
      {
	throw SerializerException("Deserializer TileMap Error : " + std::string(ex.what()));
      }

    _object.initialize("ground", "default2", "GL_QUADS");
    _object.pushVertex(glm::vec3(0, 0, 0));
    _object.pushVertex(glm::vec3(_size.x, 0, 0));
    _object.pushVertex(glm::vec3(_size.x, _size.y, 0));
    _object.pushVertex(glm::vec3(0, _size.y, 0));
    _object.pushUv(glm::vec2(0, 0));
    _object.pushUv(glm::vec2(_size.x, 0));
    _object.pushUv(glm::vec2(_size.x, _size.y));
    _object.pushUv(glm::vec2(0, _size.y));
    _object.build();
  }

  void	TileMap::save(const std::string & file)
  {

    Serializer s = Serializer::create<JSONSerializer>();

    try
      {
	s->serializeToFile("maps/" + file + ".map", *this);
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
	if (tile->getType() == Tile::Spawn)
	  _spawns.push_back(glm::ivec2(x, y));
      }
  }

  bool		TileMap::collide(int x, int y)
  {
    if (x >= _size.x || x < 0 || y < 0 || y >= _size.y)
      return (true);

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

  Tile::TileType TileMap::getTileType(int x, int y)
  {
    Tile *tile;

    tile = getTile(x, y);
    if (tile == NULL)
      return (Tile::Void);
    else
      return (tile->getType());
  }

  SerializableVector<glm::ivec2>& TileMap::getSpawns()
  {
    return (_spawns);
  }

  void		TileMap::draw(ARenderer& renderer, const RenderState& renderState,
			      const glm::vec2& position)
  {
    RenderState	newState = renderState;
    Transform	transform = renderState.transform;

    for (int y = -10; y < 10; y++)
      {
    	for (int x = -25; x < 25; x++)
    	  {
	    try
	      {
		Tile*	tile;

		tile = getTile(static_cast<int>(position.x) + x, static_cast<int>(position.y) + y);
		if (tile && tile->getDrawable() != NULL)
		  {
		    newState.transform = transform;
		    newState.transform.translate(glm::vec3(static_cast<int>(position.x) + x, static_cast<int>(position.y) + y, 0));
		    renderer.draw(*tile, newState);
		  }
	      }
	    catch (const std::exception& e)
	      {
	      }
    	  }
      }
    renderer.draw(_object, renderState);
  }
};
