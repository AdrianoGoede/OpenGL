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

    static void AddShader(GLuint program, const char* filepath, GLenum type)
    {
        const auto code{File::ReadFile(filepath)};
        if (code.empty()) {
            std::cout << "\nFile " << filepath << " is empty or was not found!";
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

    static GLuint ConstructShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path)
    {
        GLuint shader{glCreateProgram()};
        if (!shader) {
            std::cout << "\nError creating shader program!";
            return 0;
        }

        AddShader(shader, vertex_shader_path, GL_VERTEX_SHADER);
        AddShader(shader, fragment_shader_path, GL_FRAGMENT_SHADER);

        glLinkProgram(shader);
        LogErrors(shader, GL_LINK_STATUS);

        glValidateProgram(shader);
        LogErrors(shader, GL_VALIDATE_STATUS);

        return shader;
    }

    static GLint GetUniformVariableAddress(GLuint program, const GLchar* name)
    {
        glUseProgram(program);
        return glGetUniformLocation(program, name);
        glUseProgram(0);
    }

    static void AssignIntegerToUniformVariable(GLuint program, GLint var_location, GLint value)
    {
        glUseProgram(program);
        glUniform1i(var_location, value);
        glUseProgram(0);
    }
    
    static void AssignFloatToUniformVariable(GLuint program, GLint var_location, GLfloat value)
    {
        glUseProgram(program);
        glUniform1f(var_location, value);
        glUseProgram(0);
    }

    static void Assign4x4MatrixToUniformVariable(GLuint program, GLint var_location, glm::mat4& matrix)
    {
        glUseProgram(program);
        glUniformMatrix4fv(var_location, 1, GL_FALSE, glm::value_ptr(matrix));
        glUseProgram(0);
    }

};

#endif