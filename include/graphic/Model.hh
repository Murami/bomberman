#ifndef MODEL_HH
#define MODEL_HH

# include	<string>

# include	<Model.hh>
# include	<BasicShader.hh>

# include	"graphic/IDrawable.hh"
# include	"graphic/Transformable.hh"
# include	"graphic/ShaderManager.hh"

namespace bbm
{
  class	ARenderer;
  class	RenderState;

  class	Model : public IDrawable, public Transformable
  {

  public:
    Model(const std::string& path,
	  const std::string& shader,
	  float speed);
    ~Model();

    virtual void	update(float time);
    virtual void	pause();
    virtual void	play();

    void	setShader(const std::string& shader);
    void	setCurrentAnimation(const std::string& animation, bool loop);
    void	setSpeed(float speed);
    float	getSpeed() const;

  protected:
    virtual void	draw(ARenderer& renderer, const RenderState& renderState);

  protected:
    gdl::Model*		_model;
    float		_elapsedTime;
    float		_speed;
    gdl::BasicShader*	_shader;
  };
};

#endif /* MODEL_HH */
