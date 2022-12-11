#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include<vector>
#include "plane.h"
#include "mesh.h"

namespace Buffers {
    class VBO {
        public:
            // The ID allocated to the VBO
            GLuint ID;
            // VBO takes in the vertices and the size
            VBO(std::vector<MC::Vector3>& vertices, unsigned int size);
            
            void Bind();
            void Unbind();
            void Delete();
    };
}

Buffers::VBO::VBO(std::vector<MC::Vector3>& vertices, unsigned int size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
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