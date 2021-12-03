// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
// Other includes
#include <iostream>
#include <string>
#include "Others/Utilities.hpp"
#include "Models/ModelDrawer.hpp"
#include "Shaders/ShaderManager.hpp"
#include "Input/InputManager.hpp"
#include "Camera/Camera.hpp"

void Render(GLFWwindow* window);
void SetConfigs();
void SetInput(GLFWwindow* window);
void PrepareNewFrame();
void DisplayFrame(GLuint shaderProgram, GLuint vao);

int main()
{
    auto window{OpenGL_Environment::Initialize()};
    if (!window)
        return 1;
    std::cout << "\n\nInitialization Done!\n";
    Render(window);
    std::cout << "\nExiting...\n\n";
    return 0;
}

void Render(GLFWwindow* window)
{
    SetConfigs();
    SetInput(window);
    
    auto buffer{ModelDrawer::DrawHalfPyramid()};
    GLuint shaderProgram{ShaderManager::ConstructShaderProgram("Shaders/Vertex Shaders/ControllableCamera.glsl", "Shaders/Fragment Shaders/CoolGradient.glsl")};
    Camera camera{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), InitialYaw, InitialPitch, MovementSpeed, TurnSpeed};
    
    auto transMatLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "translationMatrix")};
    auto projMatLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "projectionMatrix")};
    auto viewMatLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "viewMatrix")};

    auto transMatrix{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.5f))};
    ShaderManager::Assign4x4MatrixToUniformVariable(shaderProgram, transMatLocation, transMatrix);
    
    auto projMatrix{glm::perspective(45.0f, (GLfloat)(WindowWidth / WindowHeigth), 0.1f, 100.0f)};
    ShaderManager::Assign4x4MatrixToUniformVariable(shaderProgram, projMatLocation, projMatrix);

    GLfloat deltaTime = 0.0f, lastTime = 0.0f;
    glm::mat4 viewMatrix;
    
    while (!glfwWindowShouldClose(window)) {
        
        GLfloat now = glfwGetTime();
        deltaTime = (now - lastTime);
        lastTime = now;

        PrepareNewFrame();

        camera.HandleKeyboardInput(deltaTime, InputManager::_keys);
        camera.HandleMouseInput(InputManager::_xChange, InputManager::_yChange);
        viewMatrix = camera.GetViewMatrix();
        ShaderManager::Assign4x4MatrixToUniformVariable(shaderProgram, viewMatLocation, viewMatrix);

        DisplayFrame(shaderProgram, buffer);
        glfwSwapBuffers(window);

    }
}

void SetConfigs()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void SetInput(GLFWwindow* window)
{
    InputManager::SetCallbacks(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void PrepareNewFrame()
{
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DisplayFrame(GLuint shaderProgram, GLuint vao)
{
    glUseProgram(shaderProgram);
        glBindVertexArray(vao);
            // glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    glUseProgram(0);
}