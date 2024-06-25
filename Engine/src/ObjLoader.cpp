#include "../include/ObjLoader.hpp"   


ObjLoader::ObjLoader(){
}

bool ObjLoader::init() {
  std::ifstream directory("../Engine/resources/objects");
  if (directory.good()) {
    this->m_basePath = "../Engine/resources/objects";
    return true;
  }
  return false;
}


bool ObjLoader::parse(const std::string& objFile, const std::string& textureFile,
                      Entity &entity, const unsigned int programID,
                      std::vector<float>& vertexData,std::vector<unsigned int>& indices,
                      std::vector<tinyobj::material_t>& materials) {
  
  // Parse object file information
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::string warn, err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFile.c_str(),this->m_basePath.c_str(), true);
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }
    if (!ret) {
        return false;
    }

  for (const auto& shape : shapes) {
        
    for (const auto& index : shape.mesh.indices) {
      vertexData.push_back(attrib.vertices[3 * index.vertex_index + 0]);
      vertexData.push_back(attrib.vertices[3 * index.vertex_index + 1]);
      vertexData.push_back(attrib.vertices[3 * index.vertex_index + 2]);
            
      if (!attrib.normals.empty()) {
        vertexData.push_back(attrib.normals[3 * index.normal_index + 0]);
        vertexData.push_back(attrib.normals[3 * index.normal_index + 1]);
        vertexData.push_back(attrib.normals[3 * index.normal_index + 2]);
      }
      else {
        vertexData.push_back(0.0f);
        vertexData.push_back(0.0f);
        vertexData.push_back(0.0f);
      }

      if (!attrib.texcoords.empty()) {
        vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
        vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
      }
      else {
        vertexData.push_back(0.0f);
        vertexData.push_back(0.0f);
      }
         
      indices.push_back(indices.size());
    }
  }
  

  // Parse material information
  // Set uniforms for lightning via MTL file if provided 
  if (!materials.empty()) {
    const tinyobj::material_t& material = materials[0];
    glUniform3fv(glGetUniformLocation(programID, "material.ambient"), 1, material.ambient);
    glUniform3fv(glGetUniformLocation(programID, "material.diffuse"), 1, material.diffuse);
    glUniform3fv(glGetUniformLocation(programID, "material.specular"), 1, material.specular);
    glUniform1f(glGetUniformLocation(programID, "material.shininess"), material.shininess);
  }
  else {
    // Use entity defualts
    glUniform3fv(glGetUniformLocation(programID, "material.ambient"),1, entity.get_material_ambient().data());
    glUniform3fv(glGetUniformLocation(programID, "material.diffuse"), 1, entity.get_material_diffuse().data());
    glUniform3fv(glGetUniformLocation(programID, "material.specular"), 1, entity.get_material_specular().data());
    
  }

  
  // Parse texture information
  unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    std::string texturePath = m_basePath + "/" + textureFile;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }
  entity.set_texture_id(textureID);
  return true;
}


bool ObjLoader::load(const char* objFile, const char* textureFile, Entity &entity, Renderer &renderer){ 
  
  // Parse object 
  std::vector<float> vertexData;
  std::vector<unsigned int> indices;
  std::vector<tinyobj::material_t> materials;
  std::string tinyObjPath = this->m_basePath + "/" + objFile;
  if (!ObjLoader::parse(tinyObjPath,textureFile,entity,renderer.get_programID(),vertexData,indices, materials)) {
    return false;
  }
  
  // Set the Entity VAO for drawing 
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
  
  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Texture coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  entity.set_ebo_size(indices.size());
  entity.set_vao(VAO); 
  

  return true;
}


ObjLoader::~ObjLoader(){
}
