#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include "vbo.h"

namespace Buffers {
    //! Class for Vertex Array Object
    class VAO {
        public:
            
            GLuint ID;  /*! The ID used by OpenGL to identify the buffer */
            VAO();
            //! Links the data in the VBO to the VAO
            /*!
                \param VBO The Vertex Buffer Object
                \param numComponents the number of values needed for a single vertex
                \param layout The layout where the data can be accessed
                \param type Type of data
                \param stride The amount of bytes to jump for each vertex to reach the next relevant data
                \param offset The amount of bytes to skip to reach the relevant data
            */
            void LinkVBO(VBO& VBO,GLuint numComponents, GLuint layout, GLenum type, GLsizeiptr stride, void* offset);
            //! Use the VAO
            void Bind();
            //! Prevent accidentally using the VAO
            void Unbind();
            //! Delete the VAO
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