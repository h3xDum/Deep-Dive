#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../external/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "general.hpp"

class Window {

public:
  
  Window();
  bool init();

  GLFWwindow* getGlfwWindow() const;
  bool run() const;
  ~Window();

private:
  int m_height;
  int m_width;
  const char* m_titile;
  GLFWwindow* m_window;

};


#endif 
