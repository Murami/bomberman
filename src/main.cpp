//
// main.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:54:10 2014 otoshigami
// Last update Sun Jun 15 08:54:11 2014 otoshigami
//

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
