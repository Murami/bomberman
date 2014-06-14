#ifndef RENDERSTATE_HH
# define RENDERSTATE_HH

# include "graphic/Transform.hh"

namespace bbm
{
  class	RenderState
  {
  public:
    Transform	transform;
    Transform	camera;
    Transform	projection;

  public:
    RenderState(const Transform& projection_param,
		const Transform& camera_param,
		const Transform& transform_param = Transform());
    RenderState(const RenderState& renderState);
    virtual ~RenderState();

    RenderState&	operator=(const RenderState& renderState);
  };
};

#endif /* RENDERSTATE_HH */
