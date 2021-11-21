// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Other includes
#include <iostream>
#include <string>
#include "Others/Utilities.hpp"

void Render(GLFWwindow* window);
void DisplayFrame();

int main()
{
    auto window{OpenGL_Environment::Initialize_Environment()};
    if (!window)
        return 1;
    std::cout << "\n\nInitialization Done!\n";
    Render(window);
    std::cout << "\nExiting...\n\n";
    return 0;
}

void Render(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        DisplayFrame();
    }
}

void DisplayFrame()
{
    // To Do!
}