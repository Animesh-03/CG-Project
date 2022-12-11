#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

namespace PrimitiveShapes {
    class Vertex {
        public:
            glm::vec3 position;
            glm::vec3 color;
            glm::vec3 normal;

            Vertex(glm::vec3 pos, glm::vec3 col)
            {
                position = pos;
                color = col;
            }
    };

    class SimplePlane {
        public:
            int side;
            int div;


            std::vector<Vertex> vertices;
            std::vector<GLfloat> colors;
            std::vector<GLuint> indices;
            std::vector<glm::vec3> normals;

            SimplePlane(int side, int div);
    };
}

PrimitiveShapes::SimplePlane::SimplePlane(int side, int div)
{
    this->side = side;
    this->div = div;

    float triangleSide = side/div;

    for(int row = 0; row < div + 1; row++)
    {
        for(int col = 0; col < div + 1; col++)
        {
            // vertices.push_back((float)col * triangleSide);
            // vertices.push_back((row + col)%2);
            // vertices.push_back((float)row * -triangleSide);

            vertices.push_back(Vertex(glm::vec3((float)col * triangleSide, (row + col)%2, (float)row * -triangleSide), glm::vec3(0.180392f, 0.819608f, 0.670588f)));

            colors.push_back(0.180392f);
            colors.push_back(0.819608f);
            colors.push_back(0.670588f);
        }
    }

    for(int x = 0; x < div; x++)
    {
        for(int y = 0; y < div; y++)
        {
            int index = x * (div + 1) + y;

            indices.push_back(index);
            indices.push_back(index + div + 2);
            indices.push_back(index + div + 1);

            indices.push_back(index);
            indices.push_back(index + 1);
            indices.push_back(index + div + 2);
        }
    }


    for(int index = 0; index < indices.size(); index += 3)
    {
        glm::vec3 e1 = glm::vec3(vertices[index + 1].position.x - vertices[index].position.x, vertices[index + 1].position.y - vertices[index].position.y, vertices[index + 1].position.z - vertices[index].position.z);
        glm::vec3 e2 = glm::vec3(vertices[index + 2].position.x - vertices[index].position.x, vertices[index + 2].position.y - vertices[index].position.y, vertices[index + 2].position.z - vertices[index].position.z);
    
        glm::vec3 normal = glm::cross(e1, e2);
        normal = glm::normalize(normal);

        vertices[index].normal += normal;
        vertices[index + 1].normal += normal;
        vertices[index + 2].normal += normal;
    }

}


#endif