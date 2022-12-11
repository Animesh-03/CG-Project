#ifndef HEX_COLOR_H
#define HEX_COLOR_H

#include <iostream>
#include <string>
#include <glad/glad.h>

namespace Color {
    //! Converts a hex color string into rgb colors
    class HexColor {
        public:
            HexColor(long int hexString);
            GLfloat r, g ,b; 
    };
}

Color::HexColor::HexColor(long int hexColor)
{
    long int color = hexColor;

    this->b = (color & 0xFF)/(float)255;
    this->g = (GLfloat)((color >> 8) & 0xFF)/255;
    this->r = (GLfloat)((color >> 16) & 0xFF)/255;
}

#endif