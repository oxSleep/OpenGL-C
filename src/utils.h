#ifndef UTILS_H
#define UTILS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "stdbool.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

#endif // !UTILS_H
