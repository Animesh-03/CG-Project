#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>

namespace Buffers {
    class EBO {
        public:
            // The ID alloted to the EBO
            GLuint ID;
            EBO(GLuint *indices, GLsizeiptr size);
            void Bind();
            void Unbind();
            void Delete();
    };
}

Buffers::EBO::EBO(GLuint *indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
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