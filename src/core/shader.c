//
// Created by Nikita Morozov on 06.10.2021.
//

#include <printf.h>
#include <stdlib.h>
#include "shader.h"
#include "ioutil.h"

GLuint buildShader(const char *src, GLsizei size, GLenum type, const GLint *len) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, size, &src, len);
    glCompileShader(shader);
    return shader;
}

GLuint loadShader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    GLint64 vertexShaderBufLen, fragmentShaderBufLen;
    GLchar *vertexShaderBuffer = loadFile(vertexPath, &vertexShaderBufLen);
    GLchar *fragmentShaderBuffer = loadFile(fragmentPath, &fragmentShaderBufLen);

    GLint success;
    GLchar infoLog[512];

    GLuint vertex = buildShader(vertexShaderBuffer, 1, GL_VERTEX_SHADER, NULL);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s \n %s", infoLog, vertexShaderBuffer);
    }

    GLuint fragment = buildShader(fragmentShaderBuffer, 1, GL_FRAGMENT_SHADER, NULL);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s \n %s", infoLog, fragmentShaderBuffer);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    free(vertexShaderBuffer);
    free(fragmentShaderBuffer);

    return program;
}