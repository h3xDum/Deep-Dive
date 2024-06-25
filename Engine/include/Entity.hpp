#ifndef ENTITY_HPP
#define ENTITY_HPP 

#include "Window.hpp"
#include "general.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {

public:

  Entity();
  ~Entity(); 

  unsigned int get_vao() const;
  unsigned int get_ebo_size()const;
  unsigned int get_texture_id() const;

  // material
  std::vector<GLfloat> get_material_ambient() const;
  void set_material_ambient(const GLfloat f1, const GLfloat f2, const GLfloat f3);
  
  std::vector<GLfloat> get_material_diffuse() const;
  void set_material_diffuse(const GLfloat f1, const GLfloat f2, const GLfloat f3);
  
  std::vector<GLfloat> get_material_specular() const;
  void set_material_specular(const GLfloat f1, const GLfloat f2, const GLfloat f3);
   
  // transformations
  void translate(const glm::vec3& translation);
  void rotate(float angle, const glm::vec3& axis);
  glm::mat4 get_model_matrix() const;
  

  bool shouldUpdate; // performance trick 
  void update(const unsigned int programID);

private:

  // screen vertex data 
  unsigned int m_VAO = -1;
  unsigned int m_EBOsize = -1;
  unsigned int m_textureID = -1;

  // attributes 
  float m_x , m_y , m_z = 0;
  float speed = 0;
  std::vector<GLfloat> m_material_ambient; 
  std::vector<GLfloat> m_material_diffuse;
  std::vector<GLfloat> m_material_specular;
  glm::mat4 m_model_matrix;

  // special access
  friend class ObjLoader;
  void set_vao(const unsigned int vao);
  void set_ebo_size(const unsigned int ebo_size);
  void set_texture_id(const unsigned int textureID);
};





#endif 
