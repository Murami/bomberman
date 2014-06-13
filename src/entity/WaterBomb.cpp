#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "graphic/Utils.hh"
#include "game/GameState.hh"
#include "entity/WaterBombExplode.hh"
#include "entity/WaterBomb.hh"

const float delta = 1 - 0.8;
const float translate = 0;
const float scaleFactor = 0.09 * 0.8;

namespace bbm
{
  WaterBomb::WaterBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) :
    ABomb(position, gameState, idPlayer),
    _model("WaterBomb", "default", 0)
  {
    _type = "WaterBomb";
    _model.setRoll(90);
    _model.setPosition(glm::vec3(_position.x + 0.5 + translate, _position.y + 0.5 + translate, 0.1));
    _model.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  WaterBomb::~WaterBomb()
  {
  }

  void			WaterBomb::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			WaterBomb::unpack(const ISerializedNode & current)
  {
    (void)current;
  }

  bool			WaterBomb::addExplode(float x, float y)
  {
    std::list<AEntity*>::iterator it;

    if (_gameState.getTileMap().collide(_position.x + x + 0.5, _position.y + y + 0.5))
      return (false);

    for (it = _gameState.getEntities().begin(); it != _gameState.getEntities().end(); it++)
      {
	if ((*it)->getType() == "GameBox" && (*it)->collide(glm::vec3(_position.x + x + 0.5, _position.y + y + 0.5, 0)))
	  return (false);
      }
    _gameState.addEntity(new WaterBombExplode(glm::vec2(_position.x + x, _position.y + y), _gameState));
    return (true);
  }

  void			WaterBomb::update(float time)
  {
    APlayer&	player =  _gameState.getPlayer(_idPlayer);
    glm::vec2	playerPosition = player.getPosition();
    float	delta = player.getDelta();

    if (_anim <= 2)
      {
	_anim += 0.1;
	_model.move(glm::vec3(0, 0, 0.025));
      }
    else
      {
	_anim += 0.1;
	_model.move(glm::vec3(0, 0, -0.025));
	if (_anim >= 4)
	  _anim = 0;
      }
    if (!collide(glm::vec3(playerPosition.x + 1 - delta, playerPosition.y  + 1 - delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + 1 - delta, playerPosition.y  + delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + delta, playerPosition.y + 1 - delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + delta, playerPosition.y + delta, 0)))
      _playerIsOver = false;
    _lifespan -= time;

    if (_lifespan <= 0)
      {
	int		i;
	int		j;
	int		k;
	int		l;

	_used = true;
	_gameState.getPlayer(_idPlayer).addBombsBonus();
	_gameState.addEntity(new WaterBombExplode(glm::vec2(_position.x, _position.y), _gameState));
 	for (i = 1; i != 3 && addExplode(i, 0); i++);
	for (j = 1; j != 3 && addExplode(-j, 0); j++);
 	for (k = 1; k != 3 && addExplode(0, k); k++);
	for (l = 1; l != 3 && addExplode(0, -l); l++);
	if (i >= 2 && k >= 2)
	  addExplode(1, 1);
	if (i >= 2 && l >= 2)
	  addExplode(1, -1);
	if (j >= 2 && k >= 2)
	  addExplode(-1, 1);
	if (j >= 2 && l >= 2)
	  addExplode(-1, -1);
      }
  }

  void			WaterBomb::draw(ARenderer& renderer, const RenderState& renderState)
  {
    renderer.draw(_model, renderState);
  }

  bool			WaterBomb::expired() const
  {
    return (_used);
  }

  const std::string &	WaterBomb::getType() const
  {
    return (_type);
  }

  bool			WaterBomb::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 - delta && pos.x >= _position.x + delta &&
    	pos.y < _position.y + 1 - delta && pos.y  >= _position.y + delta)
      return (true);
    return (false);
  }

  void			WaterBomb::interact(AEntity * entity)
  {
    if (entity->getType() == "PowerBombExplode" || entity->getType() == "FireBombExplode")
      _lifespan = 0;
    if (entity->getType() == "Player")
      {
	if (entity->getID() != _idPlayer || !_playerIsOver)
	  {
	    Player*	player = dynamic_cast<Player*>(entity);
	    glm::vec2	playerMove = player->getMove();
	    glm::vec2	playerPosition = player->getPosition();
	    float	delta = player->getDelta();

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
      }
  }
};
