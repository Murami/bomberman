#ifndef MARVIN_HH
#define MARVIN_HH

#include <vector>
#include "graphic/Model.hh"

namespace bbm
{
  class	Marvin : public IDrawable, public Transformable
  {
  public:
    Marvin();
    ~Marvin();

    void	setColor(const glm::vec4& color);
    void	update(float time);
    void	pause();
    void	play();

    static void	initialize();
    static void release();

  protected:
    void	draw(ARenderer& renderer, const RenderState& renderState);


  private:
    bool				_pause;
    float				_elapsedTime;
    glm::vec4				_color;
    gdl::BasicShader*			_shader;
    static std::vector<gdl::Model*>	_animations;
  };
};

#endif /* MARVIN_HH */
