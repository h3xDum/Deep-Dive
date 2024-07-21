#include "../include/InputManager.hpp"

InputManager::InputManager():
  m_window(nullptr){
}
InputManager::~InputManager(){}

bool InputManager::init(GLFWwindow* window){
  if (window == nullptr) {
    return false;
  }
  this->m_window = window;
  register_key_callBacks();
  return true;
}

void InputManager::register_key_callBacks(){
  m_keyCallBacks[GLFW_KEY_W] = [this]() { InputManager::move_up(); };
  m_keyCallBacks[GLFW_KEY_S] = [this]() { InputManager::move_down(); };
  m_keyCallBacks[GLFW_KEY_A] = [this]() { InputManager::move_left(); };
  m_keyCallBacks[GLFW_KEY_D] = [this]() { InputManager::move_right(); };
 
}

void InputManager::process_input(){
  for (const auto& pair : m_keyCallBacks) {
    if (glfwGetKey(m_window, pair.first) == GLFW_PRESS) {
      pair.second();
    }
  }
}

void InputManager::move_up(){
  glfwSetWindowShouldClose(m_window, true);
}
void InputManager::move_down(){
}
void InputManager::move_left(){
}
void InputManager::move_right(){
}

