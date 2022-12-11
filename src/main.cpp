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
#include "shaders/shaderClass.h"
#include "vao.h"
#include "ebo.h"
#include "camera.h"

const short WINDOW_WIDTH = 800;
const short WINDOW_HEIGHT = 800;
//! Writes the mesh to a .obj file
/*!
    \param mesh Reference to the mesh file to converted
*/
void writeMeshToFile(MC::Mesh &mesh)
{
    std::ofstream out;
	out.open("mesh.obj");
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

    std::cout << "Number of vertices: " << mesh.vertices.size() << std::endl;
    std::cout << "Number of indices: " << mesh.indices.size() << std::endl;
    std::cout << "Written to file\n";
}

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
    glViewport(0,0, 1920, 1080);

    Color::HexColor clearColor = Color::HexColor(0xa030cf);
    

    PerlinNoise::PerlinNoiseGenerator png(8, 0.3f, 2.0f, 25.0f, 10.5f);
    PerlinNoise::PerlinNoise pn;
    MC::CubeDomain mcDomain(100, png);

    MC::Mesh mesh;
    MC::MarchingCubes(mcDomain, mesh, 0.0f);

    writeMeshToFile(mesh);



    // Create a shader program using the default vertex and fragment shaders
    Shader::Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

    // Create a Vertex Array Object
    Buffers::VAO VAO;
    // Bind the Vertex Array Object
    VAO.Bind();

    Buffers::VBO VBO(mesh.vertices, 3 * mesh.vertices.size() * sizeof(float));
    Buffers::VBO VBO_N(mesh.normals, 3* mesh.normals.size() * sizeof(float));

    std::cout << mesh.vertices.size() << " " << mesh.normals.size() << std::endl;

    VAO.LinkVBO(VBO, 0, 3, GL_FLOAT, 3*sizeof(float), (void*) 0);
    VAO.LinkVBO(VBO_N, 1, 3, GL_FLOAT, 3*sizeof(float), (void*) 0);

    Buffers::EBO EBO(mesh.indices, mesh.indices.size() * 4);


    VBO.Unbind();
    EBO.Unbind();

    Camera::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, -0.25f, 5.0f));

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 meshPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 meshModel = glm::mat4(1.0f);
    meshModel = glm::translate(meshModel, meshPos);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        
        // Background Color of the Window
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        shaderProgram.Activate();

        // Use the VAO
        VAO.Bind();
        EBO.Bind();

        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos"), 1, glm::value_ptr(camera.position));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"),1, GL_FALSE, glm::value_ptr(meshModel));

        camera.updateMatrix(45.0f, 0.1f, 1000.0f);
        camera.Matrix(shaderProgram, "camMatrix");
        camera.HandleInputs(window);

        // Give the number of vertices to draw
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, (void *)0);

        // Swap the Front and Back Buffer Frames
        glfwSwapBuffers(window);

        // Handle events to the window
        glfwPollEvents();
    }

    EBO.Delete();
    VBO.Delete();
    VAO.Delete();
    shaderProgram.Delete();

    // Destroy the created window
    glfwDestroyWindow(window);
    
    // Terminate glfw
    glfwTerminate();
}