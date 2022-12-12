#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// Normals of vertex
out vec3 Normal;
// CUrrent position of vertex
out vec3 crntPos;

// Camera Matrix
uniform mat4 camMatrix;
// Color of light
uniform vec4 lightColor;
// Position of light
uniform vec3 lightPos;
// Model's matrix
uniform vec4 model;

void main()
{
   crntPos = vec3(model * vec4(aPos, 1.0f));

   gl_Position = camMatrix * vec4(aPos, 1.0);

   Normal = aNormal;
}