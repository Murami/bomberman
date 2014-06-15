//
// Marvin.hh for  in /home/desabr_q/Desktop/bomber/cpp_bomberman
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Sun Jun 15 08:33:55 2014 quentin desabre
// Last update Sun Jun 15 08:33:56 2014 Desabre Quentin
//

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
