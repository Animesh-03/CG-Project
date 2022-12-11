#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include "vbo.h"

namespace Buffers {
    class VAO {
        public:
            // The ID alloted to the VAO
            GLuint ID;
            VAO();
            void LinkVBO(VBO& VBO,GLuint numComponents, GLuint layout, GLenum type, GLsizeiptr stride, void* offset);
            void Bind();
            void Unbind();
            void Delete();
    };
}

Buffers::VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void Buffers::VAO::Bind()
{
    glBindVertexArray(ID);
}

void Buffers::VAO::Unbind()
{
    glBindVertexArray(0);
}

void Buffers::VAO::LinkVBO(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
   VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void Buffers::VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}


#endif