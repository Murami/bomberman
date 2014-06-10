//
// AModel.hh for bomberman in /home/manu/tek2/CPP/bomberman/model_and_animation
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Tue May 27 16:41:01 2014 Manu
// Last update Wed Jun  4 11:03:50 2014 Manu
//

#ifndef		__AMODEL_HH__
# define	__AMODEL_HH__

# include	<string>
# include	<iostream>
# include	"AObject.hh"
# include	"Model.hh"
# include	"graphic/ShaderManager.hh"
# include	"graphic/ARenderer.hh"
# include	"graphic/RenderState.hh"

namespace	bbm
{
  class		ARenderer;
  class		RenderState;

  class		AModel : public AObject
  {
  public :
    enum		Direction
      {
	FRONT = 0,
	LEFT = 1,
	BACK = 2,
	RIGHT = 3
      };

  protected :
    gdl::Model*		_model;
    const std::string	_filename;
    Direction		_direction;
    bool			_keyup;
    bool			_keydown;
    bool			_keyleft;
    bool			_keyright;
    bool			_running;
    float			_speed;
    gdl::BasicShader*	_shader;

  public :
    void		setDirection(Direction);
    Direction	getDirection() const;

  public :
    bool	initialize();
    void	draw(ARenderer&, const RenderState&);

  protected :
    virtual void	_createAnimations() = 0;

  public :
    void		setCurrentAnimation(const std::string&, bool loop = true);
    void		pause();
    void		play();

  public :
    AModel(const std::string&);
    ~AModel();
  };
}

#endif
