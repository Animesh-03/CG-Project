#ifndef MESH_H
#define MESH_H

#include <vector>
#include <math.h>

namespace MC {

    class Vector3 {
        public:
        float x, y, z;
        Vector3(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

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

        Vector3 operator- (Vector3 a)
        {
            return Vector3(this->x - a.x, this->y - a.y, this->z - a.z);
        }

        Vector3 operator+= (Vector3 a)
        {
            return Vector3(this->x + a.x, this->y + a.y, this->z + a.z);
        }

        static Vector3 cross(Vector3 v1, Vector3 v2)
        {
            return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
        }

        float length()
        {
            return std::sqrt(x*x + y*y + z*z);
        }

        void normalize()
        {
            float len = length();
            this->x = x/len;
            this->y = y/len;
            this->z = z/len;
        }
    };

    class Mesh {
        public:
            std::vector<Vector3> vertices;
            std::vector<Vector3> normals;
            std::vector<float> indices;
    };
}


#endif