// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Other includes
#include <iostream>
#include <string>
#include "Others/Utilities.hpp"
#include "Models/ModelDrawer.hpp"
#include "Shaders/ShaderManager.hpp"

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

    GLuint shader_program{ShaderManager::ConstructShaderProgram("Shaders/Vertex Shaders/Simple.glsl", "Shaders/Fragment Shaders/SolidColor.glsl")};
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT);
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