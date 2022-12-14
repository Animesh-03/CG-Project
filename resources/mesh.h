#ifndef MESH_H
#define MESH_H

#include <vector>
#include <math.h>
#include <iostream>

namespace MC {
    //! Class stores 3 float variables
    class Vector3 {
        public:
        float x, y, z;
        //! Initializes the vector with the values provided
        Vector3(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        // Returns the variable corresponding to the index provided
        float& operator[](int i)
        {
            switch(i)
            {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }
            return x;
        }

        //! Vector Subtraction on two vectors
        Vector3 operator- (Vector3 a)
        {
            return Vector3(this->x - a.x, this->y - a.y, this->z - a.z);
        }

        //! Vector addition on 2 vectors
        Vector3 operator+= (Vector3 a)
        {
            Vector3 res = Vector3(this->x + a.x, this->y + a.y, this->z + a.z);
            this->x = this->x + a.x;
            this->y = this->y + a.y;
            this->z = this->z + a.z;
            return res;
        }

        //! Returns the cross product of two vectors
        static Vector3 cross(Vector3 v1, Vector3 v2)
        {
            return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
        }

        //! Returns the length of the vector
        float length()
        {
            return std::sqrt(x*x + y*y + z*z);
        }

        //! Normalizes the vector by dividing the co-ordinates with the length
        void normalize()
        {
            float len = length();
            if(len == 0)
                len = 1;
            this->x = x/len;
            this->y = y/len;
            this->z = z/len;
        }
    };

    //! Class stores the vertices, normals and indices of the triangles
    class Mesh {
        public:
            //!Stores the vertices' position in the form of a vec3
            std::vector<Vector3> vertices;      /*! Stores the vertices' position in the form of a vec3 */
            std::vector<Vector3> normals;       /*! Stores the normals of the vertices in the form of a vec3 */
            std::vector<unsigned int> indices;  /*! Stores the indices needed to render the vertices */
    };
}


#endif