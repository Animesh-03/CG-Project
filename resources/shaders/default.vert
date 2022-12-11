#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec4 model;

void main()
{
   crntPos = vec3(model * vec4(aPos, 1.0f));

   gl_Position = camMatrix * vec4(aPos, 1.0);

   Normal = aNormal;
}