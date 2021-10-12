//
// Created by Nikita Morozov on 06.10.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "ioutil.h"

GLchar *loadFile(const GLchar *filename, GLint64 *size) {
    GLchar *buffer = 0;
    FILE *f = fopen(filename, "r");

    if (f) {
        fseek(f, 0, SEEK_END);
        *size = ftell(f) + 20;
        fseek(f, 0, SEEK_SET);
        buffer = calloc(*size, sizeof(GLchar));
        if (buffer) {
            fread(buffer, 1, *size, f);
        }
        fclose(f);
    } else {
        printf("Cant open file");
    }

    return buffer;
}