#ifndef UTILS_H
#define UTILS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdbool.h"

#define MAX_SHADER_SIZE 1024

char* parseShaderFile(const char* filePath)
{
    FILE *fp;
    size_t fileSize = 0;

    fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);

    char* shaderBuffer = (char*)malloc((fileSize + 1) * sizeof(char));    
    if (shaderBuffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    size_t bytesRead = fread(shaderBuffer, sizeof(char), fileSize, fp);
    if (bytesRead != fileSize) {
        printf("Error reading file: %zu bytes read instead of %zu\n", bytesRead, fileSize);
        free(shaderBuffer);
        return NULL;
    }

    printf("Address of buffer: %p\n", (void*)shaderBuffer);
    printf("%s\n", shaderBuffer);

    fclose(fp);
    return shaderBuffer;
}

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
