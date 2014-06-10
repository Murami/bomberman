#ifndef MODEL_HH
#define MODEL_HH

# include	<string>
# include	<Model.hh>
# include	"graphic/ShaderManager.hh"
# include	"BasicShader.hh"
# include	"graphic/IDrawable.hh"
# include	"graphic/Transformable.hh"

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

    void	setShader(const std::string& shader);
    void	setCurrentAnimation(const std::string& animation, bool loop);
    void	pause();
    void	play();
    void	update(float time);
    void	setSpeed(float speed);
    float	getSpeed() const;

  protected:
    void	draw(ARenderer& renderer, const RenderState& renderState);

  protected:
    gdl::Model		_model;

  private:
    gdl::BasicShader*	_shader;
    float		_elapsedTime;
    float		_speed;
  };
};

#endif /* MODEL_HH */
