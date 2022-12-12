#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include <vector>

namespace Buffers {
    class EBO {
        public:
            GLuint ID;  /*! The ID used by OpenGL to identify the buffer */
            //!EBO takes in the indices array and the number of indices
            EBO(std::vector<unsigned int>& indices, unsigned int size);
            // Use the EBO
            void Bind();
            // Prevent the usage of EBO
            void Unbind();
            // Delete the EBO
            void Delete();
    };
}

Buffers::EBO::EBO(std::vector<unsigned int>& indices, unsigned int size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
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