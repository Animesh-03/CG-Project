#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include<fstream>
#include<sstream>
#include<string>

std::string readFile(const char * filename);

namespace Shader {
    class Shader {
        public:
            GLuint ID;
            Shader(const char* vertexFile, const char* fragmentFile);

            void Activate();
            void Delete(); 

        private:
            void compileErrors(unsigned int shader, const char* type);
    };
}

std::string readFile(const char * filename)
{
    std::ifstream f(filename);
    std::string s;

    if(f)
    {
        std::ostringstream os;
        os << f.rdbuf();
        s = os.str();
    }

    return s;
}

Shader::Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = readFile(vertexFile);
    std::string fragmentCode = readFile(fragmentFile);

    const char *vertexCodePtr = vertexCode.c_str();
    const char *fragmentCodePtr = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodePtr, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodePtr, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "Fragment");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    compileErrors(ID, "Program");

    glLinkProgram(this->ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Shader::Activate()
{
    glUseProgram(this->ID);
}

void Shader::Shader::Delete()
{
    glDeleteProgram(this->ID);
}

void Shader::Shader::compileErrors(unsigned int shader, const char* type)
{
    GLint compileStatus;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if(compileStatus == GL_FALSE)
    {
        if(type == "Program")
        {
            glGetProgramInfoLog(shader, 512, NULL, log);
            std::cout << "SHADER PROGRAM COMPILATION FAILED:\n" << log << std::endl;
        }
        else
        {
            glGetShaderInfoLog(shader, 512, NULL, log);
            std::cout << type << " COMPILATION FAILED:\n" << log << std::endl;
        }
        throw(-1);
    }
}

#endif