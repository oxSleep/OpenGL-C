#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

#define VERTEX_FILE   "asset/shader_vertex.glsl"
#define FRAGMENT_FILE "asset/shader_fragment.glsl"

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoaderLoadGL();

    unsigned int program = loadShader(VERTEX_FILE, FRAGMENT_FILE);

    if (!program) {
        printf("Error with the shader\n");
        return 1;
    };

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO;
    glCreateBuffers(1, &VBO);
    glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glCreateVertexArrays(1, &VAO);

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3*sizeof(float));
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, false, 0);

    glEnableVertexArrayAttrib(VAO,0);

    glUseProgram(program);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
