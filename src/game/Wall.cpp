#include "game/Wall.hh"

namespace bbm
{
  Wall::Wall(const std::string& texture, const std::string& shader) :
    Object(texture, shader, GL_QUADS)
  {
    //BOTTOM SIDE
    pushVertex(glm::vec3(0, 0, 0));
    pushVertex(glm::vec3(0, 1, 0));
    pushVertex(glm::vec3(1, 1, 0));
    pushVertex(glm::vec3(1, 0, 0));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    //TOP SIDE
    pushVertex(glm::vec3(0, 0, 1));
    pushVertex(glm::vec3(1, 0, 1));
    pushVertex(glm::vec3(1, 1, 1));
    pushVertex(glm::vec3(0, 1, 1));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    //NORTH SIDE
    pushVertex(glm::vec3(0, 1, 0));
    pushVertex(glm::vec3(0, 1, 1));
    pushVertex(glm::vec3(1, 1, 1));
    pushVertex(glm::vec3(1, 1, 0));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    //SOUTH SIDE
    pushVertex(glm::vec3(0, 0, 0));
    pushVertex(glm::vec3(1, 0, 0));
    pushVertex(glm::vec3(1, 0, 1));
    pushVertex(glm::vec3(0, 0, 1));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    //EAST SIDE
    pushVertex(glm::vec3(1, 0, 0));
    pushVertex(glm::vec3(1, 1, 0));
    pushVertex(glm::vec3(1, 1, 1));
    pushVertex(glm::vec3(1, 0, 1));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    //WEST SIDE
    pushVertex(glm::vec3(0, 0, 0));
    pushVertex(glm::vec3(0, 0, 1));
    pushVertex(glm::vec3(0, 1, 1));
    pushVertex(glm::vec3(0, 1, 0));

    pushUv(glm::vec2(0, 0));
    pushUv(glm::vec2(0, 1));
    pushUv(glm::vec2(1, 1));
    pushUv(glm::vec2(1, 0));

    setColor(glm::vec4(1, 1, 1, 1));
    build();
  }

  Wall::~Wall()
  {
  }
};
