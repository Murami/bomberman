#include "graphic/RenderState.hh"

namespace bbm
{
  RenderState::RenderState(const Transform& projection_param,
			   const Transform& camera_param,
			   const Transform& transform_param)
  {
    transform = transform_param;
    projection = projection_param;
    camera = camera_param;
  }

  RenderState::RenderState(const RenderState& renderState)
  {
    *this = renderState;
  }

  RenderState::~RenderState()
  {
  }

  RenderState&	RenderState::operator=(const RenderState& renderState)
  {
    transform = renderState.transform;
    projection =  renderState.projection;
    camera =  renderState.camera;

    return (*this);
  }
};
