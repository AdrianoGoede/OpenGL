#ifndef __CAMERA__
#define __CAMERA__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

class Camera
{
private:
    
    glm::vec3 _position, _front, _up, _worldUp, _right;
    GLfloat _yaw, _pitch, _movementSpeed, _turnSpeed;

    void Update()
    {
        _front.x = (cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
        _front.y = sin(glm::radians(_pitch));
        _front.z = (sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
        _front = glm::normalize(_front);
        
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, _front));
    }

public:
    
    Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed)
    {
        _position = position;
        _worldUp = worldUp;
        _yaw = yaw;
        _pitch = pitch;
        _front = glm::vec3(0.0f, 0.0f, -1.0f);
        _movementSpeed = movementSpeed;
        _turnSpeed = turnSpeed;

        this->Update();
    }

    void HandleKeyboardInput(GLfloat deltaTime, const bool* pressedKeys, unsigned int numKeys = 1024)
    {
        GLfloat speed{deltaTime * _movementSpeed};
        
        if (pressedKeys[GLFW_KEY_W])
            _position += (_front * speed);
        
        if (pressedKeys[GLFW_KEY_S])
            _position -= (_front * speed);
        
        if (pressedKeys[GLFW_KEY_A])
            _position -= (_right * speed);
        
        if (pressedKeys[GLFW_KEY_D])
            _position += (_right * speed);
    }

    void HandleMouseInput(GLfloat& xChange, GLfloat& yChange)
    {
        xChange *= _turnSpeed;
        yChange *= _turnSpeed;

        _yaw += xChange;
        _pitch += yChange;

        _pitch = ((_pitch > 89.0f) ? 89.0f : _pitch);
        _pitch = ((_pitch < -89.0f) ? -89.0f : _pitch);

        xChange = 0.0f;
        yChange = 0.0f;

        this->Update();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(_position, (_position + _front), _up);
    }
};

#endif