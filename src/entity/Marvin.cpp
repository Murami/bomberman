#include "entity/Marvin.hh"

namespace bbm
{
  Marvin::Marvin() :
    Model("./gdl/assets/marvin.fbx", "default", 0.0025)
  {
    _model.createSubAnim(0, "startRun", 0, 30);
    _model.createSubAnim(0, "run", 38, 54);
    _model.createSubAnim(0, "stopRun", 60, 121);
  }

  Marvin::~Marvin()
  {
  }
};
