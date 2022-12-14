#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <math.h>
#include <iostream>

namespace PerlinNoise {
    static const int Perm[512] =
{
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

class PerlinNoise
{
private:
	//! The smoothing function defined Ken Perlin
	float fade(float t)
	{
		return pow(t, 3.0f) * (t * (t * 6.0f - 15.0f) + 10.0f); // 6t^5 - 15t^4 + 10t^3
	}
	//! Returns the linearly interpolated value between a and b based on the value of t
	float Lerp(float a, float b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}

public:
	//! Returns a pseudo random float based on the co-ordinates x, y, ,z and the hash value
	/*!
		\param x x-coordinate of a point
		\param y y-coordinate of a point
		\param z z-coordinate of a point
	*/
	float Gradient(int hash, float x, float y, float z)
	{
		const int h = hash & 15;
		const float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	//! Returns a pseduo random noise value baased on the given co-oridnates
	/*!
		\param x x-coordinate of a point
		\param y y-coordinate of a point
		\param z z-coordinate of a point
	*/
	float GetValue(float x, float y, float z)
	{
		// Unit coordinates in cube
		const int X = int(floor(x)) & 255;
		const int Y = int(floor(y)) & 255;
		const int Z = int(floor(z)) & 255;

		// Relative coordinates in cube
		x = x - floor(x);
		y = y - floor(y);
		z = z - floor(z);

		// Compute fading coefficients
		const float u = fade(x);
		const float v = fade(y);
		const float w = fade(z);

		// Hash cube coordinates
		const int a = Perm[X] + Y;
		const int aa = Perm[a] + Z;
		const int ab = Perm[a + 1] + Z;
		const int b = Perm[X + 1] + Y;
		const int ba = Perm[b] + Z;
		const int bb = Perm[b + 1] + Z;

		// Interpolate results
		const float l1 = Lerp(Gradient(Perm[aa], x, y, z), Gradient(Perm[ba], x - 1, y, z), u);
		const float l2 = Lerp(Gradient(Perm[ab], x, y - 1, z), Gradient(Perm[bb], x - 1, y - 1, z), u);
		const float l3 = Lerp(Gradient(Perm[aa + 1], x, y, z - 1), Gradient(Perm[ba + 1], x - 1, y, z - 1), u);
		const float l4 = Lerp(Gradient(Perm[ab + 1], x, y - 1, z - 1), Gradient(Perm[bb + 1], x - 1, y - 1, z - 1), u);
		const float l5 = Lerp(l1, l2, v);
		const float l6 = Lerp(l3, l4, v);
		return Lerp(l5, l6, w);
	}
};



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
            int frequency;          /*!< Determines the scale of the noise. Lower values give a higher variation on the noise */
            PerlinNoise pn;


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
                    value += amp * pn.GetValue(x / freq + i*3.141f, y/ freq + i*3.141f, z / freq + i*3.141f);

                    maxValue += amp;
                    amp *= pers;
                    freq *= lac;
                }
                // std::cout << "Val: " << value << std::endl;
                return value/maxValue;
            }
    };

}


#endif