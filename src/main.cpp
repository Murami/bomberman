#include "ModelManager.hpp"
#include "LetterManager.hpp"
#include "ResourceManager.hh"
#include "game/Game.hh"

bbm::ModelManager* bbm::ModelManager::_instance = NULL;
bbm::LetterManager* bbm::LetterManager::_instance = NULL;
ResourceManager* ResourceManager::_instance = NULL;

int	main()
{
  bbm::Game	game;

  return (game.run());
}
