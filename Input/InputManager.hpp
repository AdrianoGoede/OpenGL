#ifndef __INPUTMANAGER__
#define __INPUTMANAGER__

#include <GLFW/glfw3.h>

namespace InputManager
{
    static bool _keys[1024];
    GLfloat _lastX, _lastY;
    GLfloat _xChange = 0.0f, _yChange = 0.0f;
    bool _mouseAlreadyMoved{false};

    static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        else if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS)
                _keys[key] = true;
            else if (action == GLFW_RELEASE)
                _keys[key] = false;
        }
    }

    static void HandleMouse(GLFWwindow* window, double xPos, double yPos)
    {
        if (!_mouseAlreadyMoved) {
            _lastX = xPos;
            _lastY = yPos;
            _mouseAlreadyMoved = true;
        }

        _xChange = (xPos - _lastX);
        _yChange = (_lastY - yPos);

        _lastX = xPos;
        _lastY = yPos;
    }

    static void SetCallbacks(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, HandleKeys);
        glfwSetCursorPosCallback(window, HandleMouse);
    }
};

#endif