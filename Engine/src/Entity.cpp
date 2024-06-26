#include "../include/Entity.hpp"

Entity::Entity() :
  shouldUpdate(false),
  m_VAO(-1),
  m_VBO(-1),
  m_EBO(-1),
  m_EBOsize(-1),
  m_textureID(-1),
  m_material_ambient(3, 1.0f),
  m_material_diffuse(3, 0.8f),
  m_material_specular(3, 0.5f),
  m_model_matrix(glm::mat4(1.0f)){
}
Entity::~Entity(){
}

unsigned int Entity::get_vao() const {
  return this->m_VAO ;
}

void Entity::set_vao(const unsigned int vao){
  this->m_VAO = vao;
  this->shouldUpdate = true;
}

unsigned int Entity::get_ebo() const {
  return this->m_EBO;
}

void Entity::set_ebo(const unsigned int ebo) {
  this->m_EBO = ebo;
}

unsigned int Entity::get_vbo() const {
  return this->m_VBO;
}

void Entity::set_vbo(const unsigned int vbo){
  this->m_VBO = vbo;
}

unsigned int Entity::get_ebo_size() const {
  return this->m_EBOsize;
}

void Entity::set_ebo_size(const unsigned int ebo_size){
  this->m_EBOsize = ebo_size;
  this->shouldUpdate = true;
}

unsigned int Entity::get_texture_id() const {
  return this->m_textureID;
}

void Entity::set_texture_id(const unsigned int textureID) {
  this->m_textureID = textureID;
  this->shouldUpdate = true;
}

// materials 
std::vector<GLfloat> Entity::get_material_ambient() const {
  return this->m_material_ambient;
}
void Entity::set_material_ambient(const GLfloat f1, const GLfloat f2, const GLfloat f3) {
  this->m_material_ambient = {f1,f2,f3}; 
  this->shouldUpdate = true;
}

std::vector<GLfloat> Entity::get_material_diffuse() const {
  return this->m_material_diffuse;
}
void Entity::set_material_diffuse(const GLfloat f1, const GLfloat f2, const GLfloat f3) {
  this->m_material_diffuse = {f1,f2,f3}; 
  this->shouldUpdate = true;
}

std::vector<GLfloat> Entity::get_material_specular() const {
  return this->m_material_specular;
}
void Entity::set_material_specular(const GLfloat f1, const GLfloat f2, const GLfloat f3) {
  this->m_material_specular = {f1,f2,f3}; 
  this->shouldUpdate = true;
}


// transformations
void Entity::rotate(float angle, const glm::vec3& axis) {
  this->m_model_matrix = glm::rotate(this->m_model_matrix, glm::radians(angle), axis);
  this->shouldUpdate = true;   
}

void Entity::translate(const glm::vec3& translation) {
  this->m_model_matrix = glm::translate(this->m_model_matrix, translation);
  this->shouldUpdate = true;
}


glm::mat4 Entity::get_model_matrix() const {
  return m_model_matrix;

}


// state 
void Entity::update(const unsigned int programID) {
  
  // position
  GLint uniformLoc;
  uniformLoc = glGetUniformLocation(programID, "model");
  if (uniformLoc != -1) {
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(this->m_model_matrix));
  } 
    
  // material 
  glUniform3fv(glGetUniformLocation(programID, "material.ambient"),1, this->m_material_ambient.data());
  glUniform3fv(glGetUniformLocation(programID, "material.diffuse"), 1, this->m_material_diffuse.data());
  glUniform3fv(glGetUniformLocation(programID, "material.specular"), 1, this->m_material_specular.data()); 
  
  this->shouldUpdate = false;
}

















