//
// Wall.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:29:40 2014 otoshigami
// Last update Sun Jun 15 08:29:42 2014 otoshigami
//

#include "game/Wall.hh"
#include "graphic/ShaderManager.hh"
#include "graphic/TextureManager.hh"
#include "graphic/ARenderer.hh"
#include "graphic/RenderState.hh"

namespace bbm
{
  gdl::Geometry*	Wall::_geometry = NULL;

  Wall::Wall(const std::string& texture, const std::string& shader)
  {
    _shader = ShaderManager::getInstance()->getShader(shader);
    _texture = TextureManager::getInstance()->getTexture(texture);
  }

  void		Wall::draw(ARenderer& renderer, const RenderState& renderState)
  {
    RenderState	newState = renderState;

    newState.transform *= getTransform();
    renderer.draw(*_geometry, _texture, _shader, newState, GL_QUADS, glm::vec4(1, 1, 1, 1));
  }

  void		Wall::release()
  {
    delete _geometry;
  }

  void		Wall::initialize()
  {
    _geometry = new gdl::Geometry();
    //BOTTOM SIDE
    _geometry->pushVertex(glm::vec3(0, 0, 0));
    _geometry->pushVertex(glm::vec3(0, 1, 0));
    _geometry->pushVertex(glm::vec3(1, 1, 0));
    _geometry->pushVertex(glm::vec3(1, 0, 0));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    //TOP SIDE
    _geometry->pushVertex(glm::vec3(0, 0, 1));
    _geometry->pushVertex(glm::vec3(1, 0, 1));
    _geometry->pushVertex(glm::vec3(1, 1, 1));
    _geometry->pushVertex(glm::vec3(0, 1, 1));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    //NORTH SIDE
    _geometry->pushVertex(glm::vec3(0, 1, 0));
    _geometry->pushVertex(glm::vec3(0, 1, 1));
    _geometry->pushVertex(glm::vec3(1, 1, 1));
    _geometry->pushVertex(glm::vec3(1, 1, 0));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    //SOUTH SIDE
    _geometry->pushVertex(glm::vec3(0, 0, 0));
    _geometry->pushVertex(glm::vec3(1, 0, 0));
    _geometry->pushVertex(glm::vec3(1, 0, 1));
    _geometry->pushVertex(glm::vec3(0, 0, 1));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    //EAST SIDE
    _geometry->pushVertex(glm::vec3(1, 0, 0));
    _geometry->pushVertex(glm::vec3(1, 1, 0));
    _geometry->pushVertex(glm::vec3(1, 1, 1));
    _geometry->pushVertex(glm::vec3(1, 0, 1));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    //WEST SIDE
    _geometry->pushVertex(glm::vec3(0, 0, 0));
    _geometry->pushVertex(glm::vec3(0, 0, 1));
    _geometry->pushVertex(glm::vec3(0, 1, 1));
    _geometry->pushVertex(glm::vec3(0, 1, 0));

    _geometry->pushUv(glm::vec2(0, 0));
    _geometry->pushUv(glm::vec2(0, 1));
    _geometry->pushUv(glm::vec2(1, 1));
    _geometry->pushUv(glm::vec2(1, 0));

    _geometry->setColor(glm::vec4(1, 1, 1, 1));
    _geometry->build();
  }

  Wall::~Wall()
  {
  }
};
