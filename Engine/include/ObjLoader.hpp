#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP


#include "../../external/tinyobjloader/tiny_obj_loader.h"
#include "../../external/stb_image/stb_image.h"
#include "Renderer.hpp" 
#include "Entity.hpp"

class ObjLoader {

public:
  ObjLoader();
  bool init(); 
  bool load(const std::string& objFile, const std::string &textureFile, Entity &entity, Renderer &renderer) const;
  bool load(const std::string& objFile, const std::string *textureFile, Entity &entity, Renderer &renderer) const;

  ~ObjLoader();

private:
 
  std::string m_basePath;
  bool parse(const std::string& objFile,
             const std::string& textureFile,
             Entity &entity,    
             const unsigned int programID,
             std::vector<float>& vertixDate,
             std::vector<unsigned int>& indices,
             std::vector<tinyobj::material_t>& materials) const;
   
  
};


#endif 
