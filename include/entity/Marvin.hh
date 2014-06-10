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

    void	update(float time);
    void	pause();
    void	play();
    void	draw(ARenderer& renderer, const RenderState& renderState);

    static void	initialize();
    static void release();
  private:
    bool				_pause;
    gdl::BasicShader*			_shader;
    float				_elapsedTime;
    static std::vector<gdl::Model*>	_animations;
  };
};

#endif /* MARVIN_HH */
