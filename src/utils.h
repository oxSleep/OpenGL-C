#ifndef UTILS_H
#define UTILS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdbool.h"

#define MAX_SHADER_SIZE 1024

unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
char* parseFile(const char* filePath);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

unsigned int loadShader(const char* vertexPath, const char* fragmentPath)
{

    char* vertex = parseFile(vertexPath);
    char* fragment = parseFile(fragmentPath);

    if (vertex == NULL || fragment == NULL){
        return 1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    printf("%s\n", vertex);
    glShaderSource(vertexShader, 1, (const char**)&vertex, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed.\n%s", infoLog);
    }

    glShaderSource(fragmentShader, 1, (const char**)&fragment, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed.\n%s", infoLog);
    }


    unsigned int programID;
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        printf("Program linking failed.\n%s", infoLog);
    }

    free(vertex);
    free(fragment);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programID;
}

char* parseFile(const char* filePath)
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

    shaderBuffer[fileSize] = '\0';

    printf("Address of buffer: %p\n", (void*)shaderBuffer);
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
