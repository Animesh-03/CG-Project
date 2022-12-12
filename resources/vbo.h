#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include<vector>
#include "mesh.h"

namespace Buffers {
    class VBO {
        public:
            GLuint ID;  /*! The ID used by OpenGL to identify the buffer */
            //!VBO takes in the vertices and the size
            VBO(std::vector<MC::Vector3>& vertices, unsigned int size);
            //! Use the VBO
            void Bind();
            //! Prevent accidentally using the VBO
            void Unbind();
            //! Delete the VBO
            void Delete();
    };
}

Buffers::VBO::VBO(std::vector<MC::Vector3>& vertices, unsigned int size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
}

void Buffers::VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Buffers::VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffers::VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}


#endif