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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    
    auto buffer{ModelDrawer::DrawHalfPyramid()};
    GLuint shader_program{ShaderManager::ConstructShaderProgram("Shaders/Vertex Shaders/Spinning.glsl", "Shaders/Fragment Shaders/CoolGradient.glsl")};
    
    auto rotation_var_location{ShaderManager::GetUniformVariableLocation(shader_program, "rotation_degrees")};
    auto trans_mat_location{ShaderManager::GetUniformVariableLocation(shader_program, "translation_matrix")};
    auto proj_mat_location{ShaderManager::GetUniformVariableLocation(shader_program, "projection_matrix")};

    int angle{0};

    auto trans_matrix{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f))};
    ShaderManager::Assign4x4MatrixToUniformVariable(shader_program, trans_mat_location, trans_matrix);
    
    auto proj_matrix{glm::perspective(45.0f, (GLfloat)(WindowWidth / WindowHeigth), 0.1f, 1.0f)};
    ShaderManager::Assign4x4MatrixToUniformVariable(shader_program, proj_mat_location, proj_matrix);
    
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        angle = (++angle % 360);
        ShaderManager::AssignIntegerToUniformVariable(shader_program, rotation_var_location, angle);

        DisplayFrame(shader_program, buffer);
        glfwSwapBuffers(window);

    }
}

void DisplayFrame(GLuint shader_program, GLuint vao)
{
    glUseProgram(shader_program);
        glBindVertexArray(vao);
            // glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    glUseProgram(0);
}