#ifndef __UTILITIES__
#define __UTILITIES__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Parameters.h"

namespace File
{
    std::string ReadFile(const char* path)
    {
        std::ifstream fs{path};
        std::string file;
        while (fs)
            file.push_back(fs.get());
        fs.close();
        file.pop_back();
        return file;
    }
}

class OpenGL_Environment
{

private:
    
    static bool Initialize_GLFW(GLint GLversion_major, GLint GLversion_minor)
    {
        if (glfwInit())
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLversion_major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLversion_minor);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            std::cout << "\nGLFW Initialization status: SUCCESSFUL!";
            return true;
        }
        glfwTerminate();
        std::cout << "\nGLFW Initialization status: FAILED!";
        return false;
    }

    static GLFWwindow* BuildWindow(GLint width, GLint heigth, const char* title)
    {
        GLFWwindow* window{glfwCreateWindow(width, heigth, title, NULL, NULL)};
        if (window) {
            std::cout << "\nWindow Initialization status: SUCCESSFUL!";
            glfwMakeContextCurrent(window);
        }
        else {
            std::cout << "\nWindow Initialization status: ERROR!";
            glfwTerminate();
        }
        return window;
    }

    static bool Initialize_GLEW()
    {
        auto status{glewInit()};
        if (status == GLEW_OK)
        {
            glewExperimental = GL_TRUE;
            std::cout << "\nGLEW Initialization status: SUCCESSFUL!";
            return true;
        }
        std::cout << "\nGLEW Initialization status: ERROR - " << (char*)glewGetErrorString(status);
        return false;
    }

    static void SetViewport(GLFWwindow* window)
    {
        int width, heigth;
        glfwGetFramebufferSize(window, &width, &heigth);
        glViewport(0, 0, width, heigth);
    }

public:
    
    static GLFWwindow* Initialize()
    {
        GLFWwindow* window{NULL};
        
        if (!Initialize_GLFW(OpenGLversion_Major, OpenGLversion_Minor))
            return NULL;
        
        window = BuildWindow(WindowWidth, WindowHeigth, WindowTitle);
        if (window == NULL)
            return NULL;
        
        if (!Initialize_GLEW())
            return NULL;
        SetViewport(window);

        return window;
    }
};

#endif