#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <math.h>
#include <iostream>

namespace PerlinNoise {
    //! Linearly Interpolates between a and b based on the value of t
    double lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }
    //! The fade function defined by Ken Perlin
    double fade(float t)
    {
        // std::cout << "Fade: " << pow(t, 3) * (t * (t * 6 - 15) + 10) << std:: endl;
        return pow(t, 3.0f) * (t * (t * 6.0f - 15.0f) + 10.0f);
    }

    //! Returns a unique value for each co-ordinate given a hash value
    double grad(int hash, double x, double y, double z)
    {
        // switch(hash & 0xF)
        // {
        //     case 0x0: return  x + y;
        //     case 0x1: return -x + y;
        //     case 0x2: return  x - y;
        //     case 0x3: return -x - y;
        //     case 0x4: return  x + z;
        //     case 0x5: return -x + z;
        //     case 0x6: return  x - z;
        //     case 0x7: return -x - z;
        //     case 0x8: return  y + z;
        //     case 0x9: return -y + z;
        //     case 0xA: return  y - z;
        //     case 0xB: return -y - z;
        //     case 0xC: return  y + x;
        //     case 0xD: return -y + z;
        //     case 0xE: return  y - x;
        //     case 0xF: return -y - z;
        //     default: return 0;
        // }

        const int h = hash & 15;
		const float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    //! The permutation array used by Ken Perlin for noise generation
    static const int perm[] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233,
	7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
	190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219,
	203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
	20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27,
	166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230,
	220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
	63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
	200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173,
	186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118,
	126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
	189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163,
	70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19,
	98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246,
	97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
	241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181,
	199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150,
	254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128,
	195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131,
	13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69,
	142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75,
	0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
	165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229,
	122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
	102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
	187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86,
	164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124,
	123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
	227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119,
	248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172,
	9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
	185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210,
	144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239,
	107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
	115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
	67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
    };

    double perlinNoise(float x, float y, float z)
    {
        int X = (int)std::floor(x) & 255,
            Y = (int)std::floor(y) & 255,
            Z = (int)std::floor(z) & 255;

        x -= floor(x);
        y -= floor(y);
        z -= floor(z);

        

        double u = fade(x), v = fade(y), w = fade(z);

        int A = perm[X] + Y, AA = perm[A] + Z, AB = perm[A + 1] + Z;
        int B = perm[X + 1] + Y, BA = perm[B] + Z, BB = perm[B + 1] + Z;

        return (lerp(w,
                    lerp(v, 
                        lerp(u, 
                            grad(perm[AA], x  , y, z),
                            grad(perm[BA], x-1, y, z)
                        ),
                        lerp(u, 
                            grad(perm[AB], x, y-1, z),
                            grad(perm[BB], x-1, y-1, z)
                        )
                    ),
                    lerp(v,
                        lerp(u, 
                            grad(perm[AA+1], x, y, z-1),
                            grad(perm[BA+1], x-1, y, z-1)
                        ),
                        lerp(u,
                            grad(perm[AB+1], x  , y-1, z-1 ),
                            grad(perm[BB+1], x-1, y-1, z-1 )
                        )
                    )
            ));
    }



    //! Class for generating perlin noise based on the supplied parameters
    /*!
        The class takes in certain parameters based on which the perlin noise generates
        random values.
    */
    class PerlinNoiseGenerator {
        private:
            int octaves;            /*!< Determines the number of times the noise is stacked on top */
            float persistence;      /*!< Determines the amount of influence each successive octave has on the noise.
                                        Values lie between 0 and 1 */
            float lacunarity;       /*!< Determines the scale that each octave should use.
                                        Values are greater than 1  */
            float amplitude;        /*!< Determines the maximum value of noise*/
            int frequency;          /*!< Determines the scale of the noise */


        public:
            PerlinNoiseGenerator(int octaves, float persistence, float lacunarity, float amplitude, float frequency)
            {
                this->octaves = octaves;
                this->persistence = persistence;
                this->lacunarity = lacunarity;
                this->amplitude = amplitude;
                this->frequency = frequency;
            }

            double GetPerlinNoise(double x, double y, double z)
            {
                double value = 0, maxValue = 0;


                float amp = amplitude, lac = lacunarity, pers = persistence, freq = frequency;
                for(int i = 0; i < octaves; i++)
                {
                    value += amp * perlinNoise(x*freq, y*freq, z*freq);
                    // std::cout << "Val: " << perlinNoise(x*freq, y*freq, z*freq) << std::endl;

                    maxValue += amp;
                    amp *= pers;
                    freq *= lac;
                }
                std::cout << "Val: " << value << std::endl;
                return value;
            }
    };

}


#endif