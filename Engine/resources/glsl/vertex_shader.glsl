#version 330 core  
layout (location = 0) in vec3 atrPos;
layout (location = 1) in vec3 atrNormal;
layout (location = 2) in vec2 atrTexCoords;

out vec3 vertexPos;
out vec3 vertexNormal;
out vec2 vertexTexCoords;

uniform mat4 model;

void main(){
   // Transform vertex position to world space
    vec4 worldPosition = model * vec4(atrPos, 1.0);
    vertexPos = worldPosition.xyz;

    // Transform vertex normal to world space (using inverse transpose of model matrix)
    vertexNormal = mat3(transpose(inverse(model))) * atrNormal;

    // Pass texture coordinates to fragment shader
    vertexTexCoords = atrTexCoords;

    // Calculate final position of vertex (clip space)
    gl_Position = worldPosition;
}
