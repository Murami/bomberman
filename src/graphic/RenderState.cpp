//
// RenderState.cpp for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:31:16 2014 otoshigami
// Last update Sun Jun 15 08:31:17 2014 otoshigami
//

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
