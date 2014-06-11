#include <iostream>
#include <string>
#include "entity/BonusFactory.hh"
#include "entity/GameBox.hh"
#include "entity/Player.hh"
#include "entity/FireBombExplode.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"
#include "game/GameState.hh"
#include "serializer/ISerializedNode.hh"

namespace bbm
{
  GameBox::GameBox(GameState& gameState) : _wall("gamebox", "default"), _gameState(gameState)
  {

  }

  GameBox::GameBox(const glm::vec2& pos, GameState& gameState) : _wall("gamebox", "default") , _gameState(gameState)
  {
    _type = "GameBox";
    _pos = pos;
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x + 1, _pos.y, 0));
  }

  GameBox::~GameBox()
  {
  }

  void			GameBox::pack(ISerializedNode & current) const
  {
    current.add("type", _type);
    current.add("position", _pos);
  }

  void			GameBox::unpack(const ISerializedNode & current)
  {
    current.get("type", _type);
    current.get("position", _pos);
    _used = false;
    _wall.yaw(90);
    _wall.setPosition(glm::vec3(_pos.x + 1, _pos.y, 0));
  }

  void			GameBox::update(float time)
  {
    (void)time;
  }

  bool			GameBox::expired() const
  {
    return (_used);
  }

  void			GameBox::draw(ARenderer& render, const RenderState& renderState)
  {
    render.draw(_wall, renderState);
  }

  void			GameBox::collideEntity()
  {

  }

  bool			GameBox::collide(const glm::vec3 & pos)
  {
    if (pos.x  < _pos.x + 1 && (pos.x) > _pos.x &&
        pos.y < _pos.y + 1 && pos.y  > _pos.y)
      return (true);
    return (false);
  }

  void			GameBox::interact(AEntity *entity)
  {
    if (entity->getType() == "Player")
      {
	Player*	player = dynamic_cast<Player*>(entity);
	glm::vec2 playerMove = player->getMove();
	glm::vec2 playerPosition = player->getPosition();
	float delta = player->getDelta();

	if (collide(glm::vec3(playerPosition.x + playerMove.x + 1 - delta, playerPosition.y  + 1 - delta, 0)) ||
	    collide(glm::vec3(playerPosition.x + playerMove.x + 1 - delta, playerPosition.y  + delta, 0)) ||
	    collide(glm::vec3(playerPosition.x + playerMove.x + delta, playerPosition.y  + 1 - delta, 0)) ||
	    collide(glm::vec3(playerPosition.x + playerMove.x + delta, playerPosition.y  + delta, 0)))
	  playerMove.x = 0;
	if (collide(glm::vec3(playerPosition.x  + 1 - delta, playerPosition.y + playerMove.y + 1 - delta, 0)) ||
	    collide(glm::vec3(playerPosition.x  + 1 - delta, playerPosition.y + playerMove.y + delta, 0)) ||
	    collide(glm::vec3(playerPosition.x  + delta, playerPosition.y + playerMove.y + 1 - delta, 0)) ||
	    collide(glm::vec3(playerPosition.x  + delta, playerPosition.y + playerMove.y + delta, 0)))
	  playerMove.y = 0;

	player->setMove(playerMove);
      }
    if (entity->getType() == "FireBombExplode" || entity->getType() == "PowerBombExplode")
      {
	AEntity *bonus;

	dynamic_cast<ABombExplode*>(entity)->setLifeSpan(0);
	bonus = BonusFactory::getInstance()->createRandom(_pos);
	if (bonus != NULL)
	  _gameState.addEntity(bonus);
	_used = true;
      }
  }

  const std::string &	GameBox::getType() const
  {
    return (_type);
  }
};