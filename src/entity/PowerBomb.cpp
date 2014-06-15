//
// PowerBomb.cpp for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:31:05 2014 quentin desabre
// Last update Sun Jun 15 19:42:46 2014 Manu
//

#include "graphic/RenderState.hh"
#include "graphic/ARenderer.hh"
#include "graphic/Utils.hh"
#include "game/GameState.hh"
#include "entity/PowerBombExplode.hh"
#include "entity/PowerBomb.hh"
#include "sound/SoundManager.hh"

const float delta = 1 - 0.8;
const float translate = 0;
const float scaleFactor = 0.09 * 1;

namespace bbm
{
  PowerBomb::PowerBomb(GameState& gameState) : ABomb(gameState), _model("PowerBomb", "default", 0)
  {
  }

  PowerBomb::PowerBomb(const glm::vec2& position, GameState& gameState, unsigned int idPlayer) :
    ABomb(position, gameState, idPlayer),
    _model("PowerBomb", "default", 0)
  {
    _type = "PowerBomb";
    _model.setRoll(90);
    _model.setPosition(glm::vec3(_pos.x + 0.5 + translate, _pos.y + 0.5 + translate, 0.1));
    _model.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  PowerBomb::~PowerBomb()
  {
  }

  void					PowerBomb::initialize()
  {
    _type = "PowerBomb";
    _model.setRoll(90);
    _model.setPosition(glm::vec3(_pos.x + 0.5 + translate, _pos.y + 0.5 + translate, 0.1));
    _model.setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  }

  bool					PowerBomb::addExplode(float x, float y)
  {
    std::list<AEntity*>::iterator	it;
    glm::ivec2				mapsize = _gameState.getMapSize();
    std::vector<AEntity*>		map = _gameState.getGameBoxes();
    AEntity*				tmp;
    float				delta = 0.01;

    if (_gameState.getTileMap().collide(_pos.x + x + 0.5, _pos.y + y + 0.5))
      return (false);
    _gameState.addEntity(new PowerBombExplode(glm::vec2(_pos.x + x, _pos.y + y),
					      _gameState, _idPlayer));
    tmp = map[_pos.x + x + (_pos.y + y) * mapsize.x];
    if (tmp != NULL)
      {
	if (tmp->collide(glm::vec3(_pos.x + x + 1 - delta, _pos.y + y + delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + x + delta, _pos.y + y + 1 - delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + x + 0.5, _pos.y + y + 0.5, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + x + 1 - delta, _pos.y + y + 1 - delta, 0)) ||
	    tmp->collide(glm::vec3(_pos.x + x + 1 - delta, _pos.y + y + delta, 0)))
	  return (false);
      }
    return (true);
  }

  void					PowerBomb::update(float time)
  {
    APlayer&				player =  _gameState.getPlayer(_idPlayer);
    glm::vec2				playerPosition = player.getPosition();
    float				delta = player.getDelta();

    if (_anim <= 2)
      {
	_anim += 0.1;
	_model.move(glm::vec3(0, 0, 0.025));
      }
    else
      {
	_anim += 0.1;
	_model.move(glm::vec3(0, 0, -0.025));
	if (_anim >= 3.9)
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
	if (SoundManager::getInstance()->soundPlaying())
	  SoundManager::getInstance()->playSound("power");
	_used = true;
	_gameState.getPlayer(_idPlayer).addBombsBonus();
	_gameState.addEntity(new PowerBombExplode(glm::vec2(_pos.x, _pos.y), _gameState, _idPlayer));
	for (int i = 1; i != 500 && addExplode(i, 0); i++);
	for (int i = 1; i != 500 && addExplode(-i, 0); i++);
	for (int i = 1; i != 500 && addExplode(0, i); i++);
	for (int i = 1; i != 500 && addExplode(0, -i); i++);
      }
  }

  void					PowerBomb::draw(ARenderer& renderer, const RenderState& renderState)
  {
    renderer.draw(_model, renderState);
  }

  bool					PowerBomb::expired() const
  {
    return (_used);
  }

  const std::string &			PowerBomb::getType() const
  {
    return (_type);
  }

  bool					PowerBomb::collide(const glm::vec3 & pos)
  {
    if (pos.x < _pos.x + 1 - delta && pos.x >= _pos.x + delta &&
    	pos.y < _pos.y + 1 - delta && pos.y  >= _pos.y + delta)
      return (true);
    return (false);
  }

  void					PowerBomb::interact(AEntity * entity)
  {
    if (entity->getType() == "PowerBombExplode" || entity->getType() == "FireBombExplode")
      _lifespan = 0;
    if (entity->getType() == "Player" || entity->getType() == "AI")
      {
	if (entity->getID() != _idPlayer || !_playerIsOver)
	  {
	    APlayer*	player = dynamic_cast<APlayer*>(entity);
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
