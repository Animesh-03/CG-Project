#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include <vector>

namespace Buffers {
    class EBO {
        public:
            // The ID alloted to the EBO
            GLuint ID;
            EBO(std::vector<unsigned int>& indices, unsigned int size);
            void Bind();
            void Unbind();
            void Delete();
    };
}

Buffers::EBO::EBO(std::vector<unsigned int>& indices, unsigned int size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}

void Buffers::EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Buffers::EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffers::EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}


#endif