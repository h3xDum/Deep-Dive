#include "../include/Window.hpp"


Window::Window() :
  m_height(800),
  m_width(1200),
  m_titile("Deep Dive 0.1"),
  m_window(nullptr){
}

bool Window::init() {
   if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      

  
    //glfwCreateWindow(800, 1200,"Deep Dive", nullptr, nullptr);
    this->m_window =glfwCreateWindow(this->m_width,this->m_height,this->m_titile,nullptr,nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  return true;
}

GLFWwindow* Window::getGlfwWindow() const {
  return this->m_window;
}

bool Window::run() const {
  if(!glfwWindowShouldClose(this->m_window)) {
    return true;
  }
  return false;    
}



Window::~Window(){
  glfwDestroyWindow(this->m_window);
  glfwTerminate();
}
