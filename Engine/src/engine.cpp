#include "../include/Window.hpp"
#include "../include/Renderer.hpp"
#include "../include/ObjLoader.hpp"
#include "../include/Entity.hpp"
#include "../include/InputManager.hpp"
int main() {

  // Load & Init 
  Window myWindow;
  Renderer myRenderer;
  ObjLoader myObjLoader;
  InputManager myIoManager; 

  try {
    if (!myWindow.init()) { throw std::runtime_error("[!] Failed to initialize main window"); }
    if (!myRenderer.init(&myWindow)){ throw std::runtime_error("[!] Failed to initialize the Renderer"); }
    if (!myObjLoader.init()){ throw std::runtime_error("[!] Failed to initialize object loader"); }
    if (!myIoManager.init(myWindow.getGlfwWindow())){throw std::runtime_error("[!] Failed to initialize IO manager"); } 
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return -1;
  }

  // Set up scene
  Entity monkey, sun;
  if (!myObjLoader.load("sphere.obj",nullptr, sun, myRenderer)){ return -1; }
  sun.translate(glm::vec3(-0.5f , 0.5f, 0.0f)); 
  
  if (!myObjLoader.load("monkey.obj", "container.jpg", monkey, myRenderer)){ return -1; }
  monkey.translate(glm::vec3(0.5, 0.0f, 0.0f));
  monkey.rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)); 


  // Game Loop
  while (myWindow.run()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myRenderer.set_background();
    

    monkey.rotate(0.045f, glm::vec3(1.0f, 0.0f, 0.0f));
    myRenderer.draw(sun);
    myRenderer.draw(monkey);
    
    myIoManager.process_input();
    glfwSwapBuffers(myWindow.getGlfwWindow());
    glfwPollEvents();

  }

  return 0;
}

