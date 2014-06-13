//
// Frame.cpp for bomberman in /home/manu/rendu/cpp_bomberman
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Jun  5 02:47:32 2014 Manu
// Last update Fri Jun 13 15:13:08 2014 Manu
// Last update Fri Jun 13 05:56:55 2014 Desabre Quentin
//

#include		"graphic/ARenderer.hh"
#include		"graphic/RenderState.hh"
#include		"Frame.hh"

namespace		bbm
{

  Frame::Frame(const glm::vec4& color) :
    _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
  {
    this->_color = color;
    this->_explorer = NULL;
    this->_icone = NULL;
  }

  FileExplorer*	Frame::getExplorer()
  {
    return (this->_explorer);
  }

  bool		Frame::initialize()
  {
    this->_geom.setColor(this->_color);
    this->_geom.pushVertex(glm::vec3(0, 0, 0));
    this->_geom.pushVertex(glm::vec3(0, 1, 0));
    this->_geom.pushVertex(glm::vec3(0, 1, 1));
    this->_geom.pushVertex(glm::vec3(0, 0, 1));
    this->_geom.pushUv(glm::vec2(0, 0));
    this->_geom.pushUv(glm::vec2(0, 1));
    this->_geom.pushUv(glm::vec2(1, 1));
    this->_geom.pushUv(glm::vec2(1, 0));
    this->_shader = ShaderManager::getInstance()->getShader("default");
    this->_geom.build();
    if (!this->_texture.load("./assets/menu/frame/frame.tga"))
      throw (FileLoadingException("Error while loading ./assets/menu/frame/frame.tga"));
    this->_explorer = new FileExplorer(FileExplorer::SAVE_PATH);
    this->_explorer->exploreSaves();
    this->_createIcone();
    this->_createTitle();
    return (true);
  }

  void		Frame::_createIcone()
  {
    this->_icone = new Image(this->_explorer->getCurrentTexture());
    this->_icone->initialize();
    this->_icone->scale(glm::vec3(2, 3, 2));
    this->_icone->translate(glm::vec3(0.01f, 0.2f, -2));
  }

  void		Frame::_createTitle()
  {
    std::string fileName = this->_explorer->getCurrentFile();
    std::cout << "current file : " << this->_explorer->getCurrentFile() << std::endl;
    for (size_t i = 0; i < fileName.size(); i++)
      {
	if ((fileName[i] >= '0' && fileName[i] <= '9') ||
	    (fileName[i] >= 'A' && fileName[i] <= 'Z') ||
	    (fileName[i] >= 'a' && fileName[i] <= 'z') ||
	    fileName[i] == 32)
	  {
	    Letter* l = new Letter(fileName[i], glm::vec4(1, 1, 1, 1));
	    l->initialize();
	    l->translate(glm::vec3(1, -3.25, -static_cast<float>(i)/2));
	    this->_title.push_back(l);
	  }
	else if (fileName[i] == '.')
	  break;
      }
  }

  void		Frame::draw(ARenderer& renderer, const RenderState& state)
  {
    RenderState	s(state);

    s.transform = state.transform * this->getTransformation();
    glAlphaFunc(GL_GREATER, 0.9f);
    renderer.draw(this->_geom, &this->_texture, this->_shader, s, GL_QUADS);
    this->_icone->draw(renderer, state);
    for (std::list<Letter*>::iterator it = this->_title.begin();
	 it != this->_title.end(); it++)
      {
	(*it)->draw(renderer, state);
      }
  }

  void		Frame::nextSave()
  {
    this->_explorer->next();
    delete (this->_icone);
    this->_createIcone();
    this->_title.empty();
    this->_title.clear();
    this->_createTitle();
  }

  void		Frame::prevSave()
  {
    this->_explorer->prev();
    delete (this->_icone);
    this->_createIcone();
    this->_title.empty();
    this->_title.clear();
    this->_createTitle();
  }

  void		Frame::translate(const glm::vec3& t)
  {
    this->_position += t;
    if (this->_icone)
      this->_icone->translate(t);
  }

  void		Frame::rotate(const glm::vec3& r, float angle)
  {
    this->_rotation += r * angle;
    if (this->_icone)
      this->_icone->rotate(r, angle);
  }

  void		Frame::scale(const glm::vec3& s)
  {
    this->_scale *= s;
    if (this->_icone)
      this->_icone->scale(s);
  }

  glm::mat4	Frame::getTransformation()
  {
    glm::mat4	matrix(1);

    matrix = glm::translate(matrix, this->_position);
    matrix = glm::rotate(matrix, this->_rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, this->_rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, this->_rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, this->_scale);
    return (matrix);
  }

  Frame::~Frame()
  {
  }

}
