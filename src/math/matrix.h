//
// Created by Nikita Morozov on 09.10.2021.
//

#ifndef JACARANDA_STUDIO_MATRIX_H
#define JACARANDA_STUDIO_MATRIX_H

#include "vector.h"

typedef GLfloat *matrix4_t;

matrix4_t oneMatrix();

matrix4_t zeroMatrix();

matrix4_t perspective(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

matrix4_t persp(GLfloat fov, GLfloat aspectRatio, GLfloat front, GLfloat back);

matrix4_t orthographic(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

matrix4_t ortho(GLfloat fov, GLfloat aspectRatio, GLfloat front, GLfloat back);

matrix4_t translate(matrix4_t transform, vector4_t val);

matrix4_t scale(matrix4_t transform, vector4_t val);

matrix4_t rotate(matrix4_t transform, GLfloat rad, vector4_t val);

matrix4_t mul(matrix4_t a, matrix4_t b);

vector4_t mulVec(matrix4_t a, vector4_t b);

void freeMatrix(matrix4_t matrix4);

#endif //JACARANDA_STUDIO_MATRIX_H
