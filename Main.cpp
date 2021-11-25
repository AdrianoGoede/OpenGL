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

float DegreesToRadians(unsigned short degrees);
void Render(GLFWwindow* window);
void DisplayFrame(GLuint shader_program, GLuint vao);

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
    auto buffers{ModelDrawer::DrawEquilateralTriangle()};
    GLuint shader_program{ShaderManager::ConstructShaderProgram("Shaders/Vertex Shaders/Spinning.glsl", "Shaders/Fragment Shaders/SolidColor.glsl")};
    
    auto uniform_var_location{ShaderManager::GetUniformVariableAddress(shader_program, "rotation_degrees")};
    int angle{0};
    
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT);
        
        angle = ((angle % 360) + 1);
        
        ShaderManager::AssignIntegerToUniformVariable(shader_program, uniform_var_location, angle);

        DisplayFrame(shader_program, buffers.first);
        glfwSwapBuffers(window);

    }
}

void DisplayFrame(GLuint shader_program, GLuint vao)
{
    glUseProgram(shader_program);
        glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    glUseProgram(0);
}