#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "Entity.hpp"
#include "Window.hpp"

class Renderer {

public:
  
  Renderer();
  bool init(Window* window);
  unsigned int get_programID();

  void set_background();
  void draw(Entity &entity);
  
  ~Renderer();

private:
  Window* m_window;
  unsigned int m_programID;
  std::string file_to_str(const char* path);
};


#endif 
