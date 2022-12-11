#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stb/stb_img.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

#include "HexColor/hexcolor.h"
#include "PerlinNoise/perlinNoise.h"
#include "MarchingCubes/cube_domain.h"
#include "MarchingCubes/marchingCubes.h"
#include "mesh.h"

const short WINDOW_WIDTH = 800;
const short WINDOW_HEIGHT = 800;

int main()
{
    glfwInit();

    // Give Version Context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a new window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Main Window", NULL, NULL);

    //Set the window to the active window
    glfwMakeContextCurrent(window);
    // Initialize glad
    gladLoadGL();

    // Set the viewport size and position
    glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Color::HexColor clearColor = Color::HexColor(0xa030cf);

    PerlinNoise::PerlinNoiseGenerator png(2, 0.5, 2, 3, 6);
    MC::CubeDomain mcDomain(5, png);

    MC::Mesh mesh;
    MC::MarchingCubes(mcDomain, mesh, 0);

    std::ofstream out;
	out.open("test.obj");
	// if (out.is_open() == false)
	// 	return;
	out << "g " << "Obj" << std::endl;
	for (size_t i = 0; i < mesh.vertices.size(); i++)
		out << "v " << mesh.vertices.at(i).x << " " << mesh.vertices.at(i).y << " " << mesh.vertices.at(i).z << '\n';
	for (size_t i = 0; i < mesh.vertices.size(); i++)
		out << "vn " << mesh.normals.at(i).x << " " << mesh.normals.at(i).y << " " << mesh.normals.at(i).z << '\n';
	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		out << "f " << mesh.indices.at(i) + 1 << "//" << mesh.indices.at(i) + 1
			<< " " << mesh.indices.at(i + 1) + 1 << "//" << mesh.indices.at(i + 1) + 1
			<< " " << mesh.indices.at(i + 2) + 1 << "//" << mesh.indices.at(i + 2) + 1
			<< '\n';
	}
	out.close();


    while(!glfwWindowShouldClose(window))
    {
        // Swap the Front and Back Buffer Frames
        glfwSwapBuffers(window);

        // Handle events to the window
        glfwPollEvents();
    }

    


}