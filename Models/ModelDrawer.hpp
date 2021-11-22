#ifndef __MODELDRAWER__
#define __MODELDRAWER__

#include <GL/glew.h>
#include <utility>

class ModelDrawer
{
private:

    static std::pair<GLuint, GLuint> CreateBuffers(GLfloat* vertices, unsigned int size)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return std::make_pair(vao, vbo);
    }

public:

    static std::pair<GLuint, GLuint> DrawEquilateralTriangle()
    {
        GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f
        };
        return CreateBuffers(vertices, sizeof(vertices));
    }

};

#endif