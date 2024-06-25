#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../external/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "general.hpp"

class Window {

public:
  
  Window();
  bool init();

  GLFWwindow* getGlfwWindow();
  bool run();
  ~Window();

private:
  int m_height = 800;
  int m_width = 1200;
  const char* m_titile = "Deep Dive";
  
  GLFWwindow* m_window = nullptr;

};


#endif 
