//
// Created by Nikita Morozov on 06.10.2021.
//

#ifndef JACARANDA_STUDIO_VECTOR_H
#define JACARANDA_STUDIO_VECTOR_H

#include <stdbool.h>

// Include GLEW
#include "GL/glew.h"

#define ONE2_VECTOR vec2(1.0f, 1.0f)
#define ONE3_VECTOR vec3(1.0f, 1.0f, 1.0f)
#define ONE4_VECTOR vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define ZERO_VECTOR vec4(0.0f, 0.0f, 0.0f, 0.0f)
#define EQUALS_ACCURACY 1e-6f


#pragma pack(push, 1)
typedef struct Vector4 {
    GLfloat matrix[4];
    const GLfloat *x;
    const GLfloat *y;
    const GLfloat *z;
    const GLfloat *w;

} vector4_t;
#pragma pack(pop)

// instance methods
vector4_t vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

vector4_t vec3(GLfloat x, GLfloat y, GLfloat z);

vector4_t vec2(GLfloat x, GLfloat y);

// logic methods
GLfloat magnitude(vector4_t vec);

GLfloat sqrMagnitude(vector4_t vec);

GLfloat angle(vector4_t from, vector4_t to);

vector4_t clampMagnitude(vector4_t vec, GLfloat radius);

vector4_t cross3(vector4_t a, vector4_t b);

GLfloat dot(vector4_t a, vector4_t b);

vector4_t addVector(vector4_t a, vector4_t b);

vector4_t subVector(vector4_t a, vector4_t b);

vector4_t mulVector(vector4_t vec, GLfloat k);

vector4_t divVector(vector4_t vec, GLfloat k);

bool equals(vector4_t a, vector4_t b);

#endif //JACARANDA_STUDIO_VECTOR_H
