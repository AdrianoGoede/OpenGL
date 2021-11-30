#ifndef __MODELDRAWER__
#define __MODELDRAWER__

#include <GL/glew.h>
#include <utility>

class ModelDrawer
{
private:

    static GLuint InitializeVAO()
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        return vao;
    }

    static void InitializeVBO(GLfloat* vertices, unsigned int numVertices)
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);
    }

    static void InitializeIBO(GLuint* indices, unsigned int numIndices)
    {
        GLuint ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices, indices, GL_STATIC_DRAW);
    }

    static void Finish()
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    static void Cleanup()
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    static GLuint CreateBuffers(GLfloat* vertices, unsigned int numVertices, GLuint* indices, unsigned int numIndices)
    {
        GLuint vao{InitializeVAO()};
        
        InitializeVBO(vertices, numVertices);
        if (numIndices > 0)
            InitializeIBO(indices, numIndices);

        Finish();
        Cleanup();
        
        return vao;
    }

public:

    static GLuint DrawEquilateralTriangle()
    {
        GLfloat vertices[] = {
            0.0f,  1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
           -1.0f, -1.0f, 0.0f
        };
        return CreateBuffers(vertices, sizeof(vertices), nullptr, 0);
    }

    static GLuint DrawHalfPyramid()
    {
        GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
             0.0f, -1.0f, 1.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0,  0.0f
        };

        GLuint indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
        };

        return CreateBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
    }

};

#endif