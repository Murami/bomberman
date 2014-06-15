//
// Tile.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:29:04 2014 otoshigami
// Last update Sun Jun 15 08:29:06 2014 otoshigami
//

#include "game/Tile.hh"
#include "graphic/ARenderer.hh"

#include "serializer/ISerializedNode.hh"

namespace bbm
{
  Tile::Tile()
  {

  }


  Tile::Tile(bool collide, const std::string & texture,
       const std::string & shader, TileType type)
  {
    _collide = collide;
    _texture = texture;
    _shader = shader;
    _type = type;
  }

  Tile::Tile(IDrawable* drawable, bool collide) :
    _drawable(drawable),
    _collide(collide)
  {
  }

  Tile::Tile(const Tile& tile)
  {
    *this = tile;
  }

  Tile::~Tile()
  {
  }

  Tile&	Tile::operator=(const Tile& tile)
  {
    _drawable = tile._drawable;
    _collide = tile._collide;

    return (*this);
  }

  bool	Tile::getCollide()
  {
    return (_collide);
  }

  const std::string& Tile::getTexture()
  {
    return (_texture);
  }

  const std::string& Tile::getShader()
  {
    return (_shader);
  }

  Tile::TileType     Tile::getType()
  {
    return (_type);
  }

  IDrawable*	     Tile::getDrawable()
  {
    return (_drawable);
  }

  void                Tile::setDrawable(IDrawable* drawable)
  {
    _drawable = drawable;
  }

  void	Tile::draw(ARenderer& renderer, const RenderState& renderState)
  {
    renderer.draw(*_drawable, renderState);
  }

  void	Tile::pack(ISerializedNode & current) const
  {
    current.add("collide", _collide);
    current.add("type", _type);
    current.add("texture", _texture);
    current.add("shader", _shader);
  }

  void	Tile::unpack(const ISerializedNode & current)
  {
    int type;

    current.get("collide", _collide);
    current.get("type", type);
    current.get("texture", _texture);
    current.get("shader", _shader);
    _type = static_cast<bbm::Tile::TileType>(type);
  }
};
