//
// Created by Nikita Morozov on 09.10.2021.
//

#include <stdlib.h>
#include <math.h>
#include "math.h"
#include "matrix.h"

#define cord(r, c, n) (r*n+c)

static const int N = 4;

/// create new one matrix
matrix4_t oneMatrix() {
    matrix4_t one = (matrix4_t) calloc(N * N, sizeof(GLfloat));
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            one[r * N + c] = r == c ? 1 : 0;
        }
    }

    return one;
}

/// create new one matrix
matrix4_t zeroMatrix() {
    matrix4_t zero = (matrix4_t) calloc(N * N, sizeof(GLfloat));
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            zero[r * N + c] = 0;
        }
    }

    return zero;
}

matrix4_t persp(GLfloat fov, GLfloat aspectRatio, GLfloat front, GLfloat back) {
    GLfloat tan = tanf(rad(fov / 2));
    GLfloat height = front * tan;
    GLfloat width = height * aspectRatio;

    return perspective(-width, width, -height, height, front, back);
}

matrix4_t perspective(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) {
    matrix4_t res = zeroMatrix();

    res[0] = 2.f * zNear / (right - left);
    res[2] = (right + left) / (right - left);
    res[N + 1] = 2.f * zNear / (top - bottom);
    res[N + 2] = (top + bottom) / (top - bottom);
    res[2 * N + 2] = -(zFar + zNear) / (zFar - zNear);
    res[2 * N + 3] = -(2.f * zFar * zNear) / (zFar - zNear);
    res[3 * N + 2] = -1.f;

    return res;
}

matrix4_t ortho(GLfloat fov, GLfloat aspectRatio, GLfloat front, GLfloat back){
    GLfloat tan = tanf(rad(fov / 2));
    GLfloat height = front * tan;
    GLfloat width = height * aspectRatio;

    return orthographic(-width, width, -height, height, front, back);
}

matrix4_t orthographic(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) {
    matrix4_t res = zeroMatrix();

    res[0] = 2.f / (right - left);
    res[3] = -(right + left) / (right - left);
    res[N + 1] = 2.f / (top - bottom);
    res[N + 3] = -(top + bottom) / (top - bottom);
    res[N * 2 + 2] = -2.f / (zFar - zNear);
    res[N * 2 + 3] = -(zFar + zNear) / (zFar - zNear);
    res[N * 3 + 3] = 1.f;

    return res;
}

/// translate with projection
matrix4_t translate(matrix4_t transform, vector4_t val) {
    // set forth pos to 1 because default 0 for vec3
    val.matrix[3] = 1.0f;

    // build transform matrix
    matrix4_t tmp = oneMatrix();
    for (int i = 0; i < N; i++) {
        tmp[i * N + N - 1] = val.matrix[i];
    }

    // combine with previous transforms
    matrix4_t res = mul(transform, tmp);

    // free temporary and prev values
    freeMatrix(transform);
    freeMatrix(tmp);

    return res;
}

/// scale vector
matrix4_t scale(matrix4_t transform, vector4_t val) {
    // set forth pos to 1 because default 0 for vec3
    val.matrix[3] = 1.0f;

    // build transform matrix
    matrix4_t tmp = oneMatrix();
    for (int i = 0; i < N; i++) {
        tmp[i * N + i] = val.matrix[i];
    }

    // combine with previous transforms
    matrix4_t res = mul(transform, tmp);

    // free temporary and prev values
    freeMatrix(transform);
    freeMatrix(tmp);

    return res;
}

/// matrix multiplication using standard math algorithm
matrix4_t rotate(matrix4_t transform, GLfloat rad, vector4_t val) {
    matrix4_t tmp = oneMatrix();

    GLfloat n[3];
    GLfloat l = sqrMagnitude(val);
    n[0] = *val.x / l;
    n[1] = *val.y / l;
    n[2] = *val.z / l;

    GLfloat cosTheta = cosf(rad);
    GLfloat sinTheta = sinf(rad);

    GLfloat sign;
    for (int r = 0; r < 3; r++) {
        sign = r % 2 == 0 ? 1 : -1;
        for (int c = 0; c < 3; c++) {
            if (r == c) {
                GLfloat d = n[r] * n[r];
                tmp[r * N + c] = d + (1 - d) * cosTheta;
            } else {
                tmp[r * N + c] = n[r] * n[c] * (1 - cosTheta) + sign * n[3 - r - c] * sinTheta;
                sign *= -1;
            }
        }
    }

    // combine with previous transforms
    matrix4_t res = mul(transform, tmp);

    // free temporary and prev values
    freeMatrix(transform);
    freeMatrix(tmp);

    return res;
}

/// matrix multiplication using standard math algorithm
matrix4_t mul(matrix4_t a, matrix4_t b) {
    matrix4_t zero = zeroMatrix();

    for (int k = 0; k < N; k++) {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                zero[r * N + c] += a[r * N + k] * b[k * N + c];
            }
        }
    }

    return zero;
}

vector4_t mulVec(matrix4_t a, vector4_t b) {
    vector4_t res = ONE3_VECTOR;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            res.matrix[r] += a[r * N + c] * b.matrix[c];
        }
    }

    return res;
}


/// free matrix
void freeMatrix(matrix4_t matrix4) {
    free(matrix4);
}

