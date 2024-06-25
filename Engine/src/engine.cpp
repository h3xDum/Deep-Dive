#include "../include/Window.hpp"
#include "../include/Renderer.hpp"
#include "../include/ObjLoader.hpp"
#include "../include/Entity.hpp"

int main() {

  // Load & Init 
  Window myWindow;
  Renderer myRenderer;
  ObjLoader myObjLoader;

  try {
    if (!myWindow.init()) { throw std::runtime_error("[!] Failed to initialize main window"); }
    if (!myRenderer.init(&myWindow)){ throw std::runtime_error("[!] Failed to initialize the Renderer"); }
    if (!myObjLoader.init()){ throw std::runtime_error("[!] Failed to initialize object loader"); }
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return -1;
  }

  // Set up scene
  Entity monkey, sun;
  if (!myObjLoader.load("sphere.obj","container.jpg", sun, myRenderer)){ return -1; }
  sun.translate(glm::vec3(-0.5f , 0.5f, 0.0f)); 
  
  if (!myObjLoader.load("monkey.obj", "container.jpg", monkey, myRenderer)){ return -1; }
  monkey.translate(glm::vec3(0.5, 0.0f, 0.0f));
  monkey.rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)); 


  // Game Loop
  while (myWindow.run()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myRenderer.set_background();
    
    //sun.translate(glm::vec3(0.0002f, 0.0f, 0.0f));
    monkey.rotate(0.045f, glm::vec3(1.0f, 0.0f, 0.0f));
    myRenderer.draw(sun);
    myRenderer.draw(monkey);
    

    glfwSwapBuffers(myWindow.getGlfwWindow());
    glfwPollEvents();
  }

  return 0;
}

