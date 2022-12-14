#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

#include "shaders/shaderClass.h"

namespace Camera {
    class Camera
    {
        public:
            glm::vec3 position;     /*! The position of the camera */
            glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f); /*! The rotation of the camera */
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);     /*! The up vector of the camera */
            //! The constructor takes in the Window width and height as well as the initial position of the camera
            Camera(int width, int height, glm::vec3 position);
            //! Update the attributes of the camera
            /*!
                \param FOV The field of vision of the camera. Lowering this results in a zoom effect
                \param nearClip The distance of the nearClip Plane from the camera
                \param farClip The distance of the farClip Plane from the camera
            */
            void updateMatrix(float FOV, float nearClip, float farClip);
            //! Update the camera matrix used by the shader to render objects
            /*! 
                \param shader The reference to the shaderProgram
                \param uniform The name of the uniform used in the shader code
            */
            void Matrix(Shader::Shader &shader, const char* uniform);
            
            //! Responds to the input by the user to handle camera movement
            /*!
                \param window The reference to the window the camera is used in
            */
            void HandleInputs(GLFWwindow * window);

        private:
            int width;      /*! The width of the window */
            int height;     /*! The height of the window */
            glm::mat4 cameraMatrix;     /*! The matrix obtained by projection * view */

            float speed = 0.5f;         /*! The speed of camera movement */
            float sensitivity = 60.0f;  /*! The rotation sensitivity of the camera */

            bool firstClick;

    };
}


Camera::Camera::Camera(int width, int height, glm::vec3 position)
{
    this->width = width;
    this->height = height;
    this->position = position;
}

void Camera::Camera::updateMatrix(float FOV, float nearClip, float farClip)
{
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = glm::lookAt(position, position + rotation, up);
    projection = glm::perspective(glm::radians(FOV), (float)width/height, nearClip, farClip);

    cameraMatrix = projection * view;
}

void Camera::Camera::Matrix(Shader::Shader &shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Camera::HandleInputs(GLFWwindow * window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= speed * glm::normalize(glm::cross(rotation, up));
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= speed * rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * glm::normalize(glm::cross(rotation, up));
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * up;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        // position -= speed * up;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if(firstClick)
        {
            firstClick = false;
        }
        else
        {
            float rotY = sensitivity * (mouseX - width/2)/width;
            float rotX = sensitivity * (mouseY - height/2)/height;

            glm::vec3 newRotation = glm::rotate(rotation, glm::radians(-rotX), glm::normalize(glm::cross(rotation, up)));

            if(!(glm::angle(newRotation, up) <= glm::radians(3.0f) || glm::angle(newRotation, up) <= glm::radians(3.0f)))
            {
                rotation = newRotation;
            }

            rotation = glm::rotate(rotation, glm::radians(-rotY), up);
        }

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}


#endif