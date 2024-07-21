#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "Window.hpp"
#include "general.hpp"
#include <unordered_map>

class InputManager {

public:
  InputManager();
  ~InputManager();

  bool init(GLFWwindow *window);
  void process_input();

private:
  GLFWwindow* m_window; 
  std::unordered_map<int, std::function<void()>> m_keyCallBacks;     
  void register_key_callBacks();

  void move_up();
  void move_down();
  void move_right();
  void move_left();



}; 






#endif

