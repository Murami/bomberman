//
// RenderState.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:34:15 2014 otoshigami
// Last update Sun Jun 15 08:34:16 2014 otoshigami
//

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
