#ifndef CUBE_DOMAIN_H
#define CUBE_DOMAIN_H

#include <iostream>
#include <vector>

#include "../PerlinNoise/perlinNoise.h"

namespace MC {
    //! Class for the domain needed for the marching cubes algorithm
    class CubeDomain {
        public:
            //! Constructor for the class takes in the size of the cube and the reference to the perlin noise generator
            /*!
                \param size The size of the cube's edge inside which the domain will be generated
                \param png The reference to the noise generator which assigns each point inside the domain a value
            */
            CubeDomain(int size, PerlinNoise::PerlinNoiseGenerator &png);
            /*!
                Creates a cubical domain with a single octave and given frequency
                \param size Defines the size of the domain
                \param pn The perlin noise generator to use
                \param frequency The frequency to be used on the noise generation
            */
            CubeDomain(int size, PerlinNoise::PerlinNoise &pn, int frequency);
            CubeDomain();
            //! A 3D array which stores the value of each co-ordinate inside the domain
            std::vector<std::vector<std::vector<float>>> domain;
            //! The size of the domain
            int size;

            void printDomain();
    };
}

MC::CubeDomain::CubeDomain()
{
    size = 0;
}

MC::CubeDomain::CubeDomain(int size, PerlinNoise::PerlinNoiseGenerator &png)
{
    domain = std::vector<std::vector<std::vector<float>>>(size, std::vector<std::vector<float>>(size, std::vector<float>(size, 0)));
    this->size = size;
    
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size; k++)
            {
                domain[i][j][k] = png.GetPerlinNoise(i, j, k);
            }
        }
    }
}

MC::CubeDomain::CubeDomain(int size, PerlinNoise::PerlinNoise &pn, int frequency)
{
    domain = std::vector<std::vector<std::vector<float>>>(size, std::vector<std::vector<float>>(size, std::vector<float>(size, 0)));
    this->size = size;
    
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size; k++)
            {
                domain[i][j][k] = pn.GetValue(i*frequency,j*frequency,k*frequency);
            }
        }
    }
}

void MC::CubeDomain::printDomain()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size; k++)
            {
                std::cout << domain[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

#endif