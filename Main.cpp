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

float DegreesToRadians(int degrees);
void Render(GLFWwindow* window);
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

float DegreesToRadians(int degrees) { return ((degrees * 3.1415f) / 180); }

void Render(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    
    auto buffer{ModelDrawer::DrawHalfPyramid()};
    GLuint shaderProgram{ShaderManager::ConstructShaderProgram("Shaders/Vertex Shaders/Spinning.glsl", "Shaders/Fragment Shaders/CoolGradient.glsl")};
    
    auto transMatLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "translationMatrix")};
    auto projMatLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "projectionMatrix")};
    auto rotationRadiansLocation{ShaderManager::GetUniformVariableLocation(shaderProgram, "rotationRadians")};

    int angle{0};

    auto transMatrix{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f))};
    ShaderManager::Assign4x4MatrixToUniformVariable(shaderProgram, transMatLocation, transMatrix);
    
    auto projMatrix{glm::perspective(45.0f, (GLfloat)(WindowWidth / WindowHeigth), 0.1f, 1.0f)};
    ShaderManager::Assign4x4MatrixToUniformVariable(shaderProgram, projMatLocation, projMatrix);
    
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        angle = (++angle % 360);
        ShaderManager::AssignFloatToUniformVariable(shaderProgram, rotationRadiansLocation, DegreesToRadians(angle));

        DisplayFrame(shaderProgram, buffer);
        glfwSwapBuffers(window);

    }
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