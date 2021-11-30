#ifndef __SHADERMANAGER__
#define __SHADERMANAGER__

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../Others/Utilities.hpp"

class ShaderManager
{
private:

    static void AddShader(GLuint program, const char* filePath, GLenum type)
    {
        const auto code{File::ReadFile(filePath)};
        if (code.empty()) {
            std::cout << "\nFile " << filePath << " is empty or was not found!";
            return;
        }

        const GLchar* codeptr[1] = {code.c_str()};
        const GLint codelength[1] = {(GLint)code.length()};

        GLuint shader{glCreateShader(type)};
        glShaderSource(shader, 1, codeptr, codelength);
        glCompileShader(shader);

        LogErrors(shader, GL_COMPILE_STATUS);

        glAttachShader(program, shader);
    }

    static void LogErrors(GLuint shader, GLenum type)
    {
        GLint result{0};
        GLchar message[1024];

        if (type == GL_COMPILE_STATUS)
            glGetShaderiv(shader, type, &result);
        else
            glGetProgramiv(shader, type, &result);

        if (!result) {
            if (type == GL_COMPILE_STATUS)
                glGetShaderInfoLog(shader, sizeof(message), NULL, message);
            else
                glGetProgramInfoLog(shader, sizeof(message), NULL, message);
            std::cout << "\nError: " << message;
        }
    }

public:

    static GLuint ConstructShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        GLuint shader{glCreateProgram()};
        if (!shader) {
            std::cout << "\nError creating shader program!";
            return 0;
        }

        AddShader(shader, vertexShaderPath, GL_VERTEX_SHADER);
        AddShader(shader, fragmentShaderPath, GL_FRAGMENT_SHADER);

        glLinkProgram(shader);
        LogErrors(shader, GL_LINK_STATUS);

        glValidateProgram(shader);
        LogErrors(shader, GL_VALIDATE_STATUS);

        return shader;
    }

    static GLuint GetUniformVariableLocation(GLuint program, const GLchar* name)
    {
        glUseProgram(program);
        return glGetUniformLocation(program, name);
        glUseProgram(0);
    }

    static void AssignIntegerToUniformVariable(GLuint program, GLint varLocation, GLint value)
    {
        glUseProgram(program);
        glUniform1i(varLocation, value);
        glUseProgram(0);
    }
    
    static void AssignFloatToUniformVariable(GLuint program, GLint varLocation, GLfloat value)
    {
        glUseProgram(program);
        glUniform1f(varLocation, value);
        glUseProgram(0);
    }

    static void Assign4x4MatrixToUniformVariable(GLuint program, GLint varLocation, glm::mat4& matrix)
    {
        glUseProgram(program);
        glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(matrix));
        glUseProgram(0);
    }

};

#endif