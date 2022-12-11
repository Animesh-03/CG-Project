#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <shaders/shaderClass.h>
#include <stb/stb_img.h>

namespace Textures {
    class Texture {
        public: 
            GLuint ID;
            GLenum type;

            Texture(const char* imageFile, GLenum texType, GLenum slot, GLenum format, GLenum pixelFormat);

            void TexUnit(Shader::Shader shader, const char* uniform, GLuint unit);
            void Bind();
            void Unbind();
            void Delete();
    };
}

Textures::Texture::Texture(const char* imageFile, GLenum texType, GLenum slot, GLenum format, GLenum pixelFormat)
{
    this->type = texType;

    int imgWidth, imgHeight, imgNumCol;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(imageFile, &imgWidth, &imgHeight, &imgNumCol, 0);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelFormat, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Textures::Texture::TexUnit(Shader::Shader shader, const char* uniform, GLuint unit) 
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1f(texUni, unit);
}

void Textures::Texture::Bind()
{
    glBindTexture(type, ID);
}

void Textures::Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Textures::Texture::Delete()
{
    glDeleteTextures(1, &ID);
}

#endif