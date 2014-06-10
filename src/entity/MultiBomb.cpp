#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "graphic/Utils.hh"
#include "game/GameState.hh"
#include "entity/FireBomb.hh"
#include "entity/MultiBomb.hh"

const float delta = 1 - 0.8;
const float translate = 0;
const float scaleFactor = 0.09 * 0.8;

namespace bbm
{
  MultiBomb::MultiBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) :
    ABomb(position, gameState, idPlayer),
    _model("./models_bombs/WindBomb/WindBomb.obj", "default", 0)
  {
    _type = "MultiBomb";
    _model.setRoll(90);
    _model.setPosition(glm::vec3(_position.x + 0.5 + translate, _position.y + 0.5 + translate, 0.1));
    _model.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  MultiBomb::~MultiBomb()
  {
  }

  void			MultiBomb::pack(ISerializedNode & current) const
  {
    (void)current;
  }

  void			MultiBomb::unpack(const ISerializedNode & current)
  {
    (void)current;
  }

  bool			MultiBomb::addExplode(float x, float y)
  {
    std::list<AEntity*>::iterator it;

    if (_gameState.getTileMap().collide(_position.x + x + 0.5, _position.y + y + 0.5))
      return (false);

    _gameState.addEntity(new FireBomb(glm::vec2(_position.x + x, _position.y + y), _gameState, _idPlayer));
    for (it = _gameState.getEntities().begin(); it != _gameState.getEntities().end(); it++)
      {
	if ((*it)->getType() == "GameBox" && (*it)->collide(glm::vec3(_position.x + x + 0.5, _position.y + y + 0.5, 0)))
	  return (false);
      }
    return (true);
  }

  void			MultiBomb::update(float time)
  {
    Player&	player =  _gameState.getPlayer(_idPlayer);
    glm::vec2	playerPosition = player.getPosition();
    float	delta = player.getDelta();

    if (!collide(glm::vec3(playerPosition.x + 1 - delta, playerPosition.y  + 1 - delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + 1 - delta, playerPosition.y  + delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + delta, playerPosition.y + 1 - delta, 0)) &&
	!collide(glm::vec3(playerPosition.x + delta, playerPosition.y + delta, 0)))
      _playerIsOver = false;
    _lifespan -= time;

    if (_lifespan <= 0)
      {
	_used = true;
	_gameState.getPlayer(_idPlayer).addBombsBonus();
	_gameState.addEntity(new FireBomb(glm::vec2(_position.x, _position.y), _gameState, _idPlayer));
	for (int i = 1; i !=  _gameState.getPlayer(_idPlayer).getPower()
	       && addExplode(i, 0); i++);
	for (int i = 1; i !=  _gameState.getPlayer(_idPlayer).getPower()
	       && addExplode(-i, 0); i++);
	for (int i = 1; i !=  _gameState.getPlayer(_idPlayer).getPower()
	       && addExplode(0, i); i++);
	for (int i = 1; i !=  _gameState.getPlayer(_idPlayer).getPower()
	       && addExplode(0, -i); i++);
      }
  }

  void			MultiBomb::draw(ARenderer& renderer, const RenderState& renderState)
  {
    renderer.draw(_model, renderState);
  }

  bool			MultiBomb::expired() const
  {
    return (_used);
  }

  const std::string &	MultiBomb::getType() const
  {
    return (_type);
  }

  bool			MultiBomb::collide(const glm::vec3 & pos)
  {
    if (pos.x < _position.x + 1 - delta && pos.x >= _position.x + delta &&
    	pos.y < _position.y + 1 - delta && pos.y  >= _position.y + delta)
      return (true);
    return (false);
  }

  void			MultiBomb::interact(AEntity * entity)
  {
    if (entity->getType() == "PowerBombExplode" || entity->getType() == "MultiBombExplode")
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
