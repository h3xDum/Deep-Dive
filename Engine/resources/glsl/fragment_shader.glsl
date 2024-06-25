#version 330 core

in vec3 vertexPos;
in vec3 vertexNormal;
in vec2 vertexTexCoords;

out vec4 fragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform sampler2D ourTexture;


void main() {
  /* basic Phong lighting */

  // setting light source
  vec3 lightColor  = vec3(1.0, 1.0, 1.0);
  vec3 lightSource = vec3(1.0, 0.0, 0.0);

  // calculating ambient
  vec3 ambient = material.ambient;

  // calculating diffuse
  vec3 norm = normalize(vertexNormal);
  vec3 lightDir = normalize(lightSource - vertexPos);
  float diffuseStrength = max(0.0, dot(lightDir, norm));
  vec3 diffuse = material.diffuse * diffuseStrength * lightColor;

  // calculating specular (currently set to zero)
  vec3 specular = vec3(0.0, 0.0, 0.0);

  // final lighting = ambient + diffuse + specular
  vec3 lighting = ambient + diffuse + specular;

  // model final color = vertexColor * lighting
  vec3 vertexColor = vec3(0.75, 0.75, 0.75);
  vec3 modelColor = vertexColor * lighting;
  


  // output 
  fragColor = texture(ourTexture,vertexTexCoords);
}

