#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP


#include "../../external/tinyobjloader/tiny_obj_loader.h"
#include "../../external/stb_image/stb_image.h"
#include "Renderer.hpp" // no need for it. but included for glfw
#include "Entity.hpp"

class ObjLoader {

public:
  ObjLoader();
  bool init(); // check & set the objects location folder
  bool load(const char* objFile, const char* textureFile, Entity &entity, Renderer &renderer);

  ~ObjLoader();

private:
  bool parse(const std::string& objFile,
             const std::string& textureFile,
             Entity &entity,    
             const unsigned int programID,
             std::vector<float>& vertixDate,
             std::vector<unsigned int>& indices,
             std::vector<tinyobj::material_t>& materials);
   
  
  std::string m_basePath = "";
};


#endif 
