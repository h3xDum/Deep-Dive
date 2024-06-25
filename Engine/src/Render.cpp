#include "../include/Renderer.hpp"


Renderer::Renderer() : m_window(nullptr),m_programID(0) {
}

std::string Renderer::file_to_str(const char* path) {
    std::ifstream ifstream;
    ifstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream sstream;
    try {
        ifstream.open(path);
        sstream << ifstream.rdbuf();
        ifstream.close();
    } catch (std::ifstream::failure& e) {
        std::cout << "[!] in file: " << path << std::endl;
        throw std::runtime_error("ERROR::Failed to read the file.");
    }
    return sstream.str();
}

bool Renderer::init(Window* window) {
    std::string vShaderSource;
    std::string fShaderSource;
    char infoLog[512];
    int success;

    try {
        vShaderSource = Renderer::file_to_str("../Engine/resources/glsl/vertex_shader.glsl").c_str();
        fShaderSource = Renderer::file_to_str("../Engine/resources/glsl/fragment_shader.glsl").c_str();
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    unsigned int vShader, fShader;
    const char* szVshaderSource = vShaderSource.c_str();
    const char* szFshaderSource = fShaderSource.c_str();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &szVshaderSource, nullptr);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::Failed to compile vertex shader " << infoLog << std::endl;
        return false;
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &szFshaderSource, nullptr);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::Failed to compile fragment shader " << infoLog << std::endl;
        return false;
    }

    this->m_programID = glCreateProgram();
    glAttachShader(this->m_programID, vShader);
    glAttachShader(this->m_programID, fShader);
    glLinkProgram(this->m_programID);
    glGetProgramiv(this->m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->m_programID, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::Failed to link shader program" << infoLog << std::endl;
        return false;
    }

    glUseProgram(this->m_programID);
    this->m_window = window;
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return true;
}

void Renderer::set_background() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Renderer::get_programID() {
    return this->m_programID;
}

void Renderer::draw(Entity &entity) {
    if (entity.shouldUpdate) {
      // position
      GLint uniformLoc;
      uniformLoc = glGetUniformLocation(this->m_programID, "model");
      if (uniformLoc != -1) {
      glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(entity.get_model_matrix()));
      } 
      // material 
      glUniform3fv(glGetUniformLocation(this->m_programID, "material.ambient"),1, entity.get_material_ambient().data());
      glUniform3fv(glGetUniformLocation(this->m_programID, "material.diffuse"), 1, entity.get_material_diffuse().data());
      glUniform3fv(glGetUniformLocation(this->m_programID, "material.specular"), 1, entity.get_material_specular().data()); 
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, entity.get_texture_id());
  
    
  /*
  // position
  GLint uniformLoc;
  uniformLoc = glGetUniformLocation(this->m_programID, "model");
  if (uniformLoc != -1) {
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(entity.get_model_matrix()));
  } 
    
  // material 
  glUniform3fv(glGetUniformLocation(this->m_programID, "material.ambient"),1, entity.get_material_ambient().data());
  glUniform3fv(glGetUniformLocation(this->m_programID, "material.diffuse"), 1, entity.get_material_diffuse().data());
  glUniform3fv(glGetUniformLocation(this->m_programID, "material.specular"), 1, entity.get_material_specular().data()); 
  */

  glBindVertexArray(entity.get_vao());
  glDrawElements(GL_TRIANGLES, entity.get_ebo_size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Renderer::~Renderer() {
    glDeleteProgram(this->m_programID);
}
















