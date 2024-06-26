#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "Entity.hpp"
#include "Window.hpp"

class Renderer {

public:
  
  Renderer();
  bool init(Window* window);
  unsigned int get_programID() const;

  void set_background() const ;
  void draw(const Entity &entity) const ;
  
  ~Renderer();

private:
  Window* m_window;
  unsigned int m_programID;
  std::string file_to_str(const char* path) const;
};


#endif 
