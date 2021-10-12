//
// Created by Nikita Morozov on 06.10.2021.
//

#include <math.h>
#include "vector.h"
#include "math.h"

vector4_t vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    vector4_t tmp = {
            {x, y, z, w},
            &tmp.matrix[0],
            &tmp.matrix[1],
            &tmp.matrix[2],
            &tmp.matrix[3]
    };

    return tmp;
}

vector4_t vec3(GLfloat x, GLfloat y, GLfloat z) {
    return vec4(x, y, z, 0.0f);
}

vector4_t vec2(GLfloat x, GLfloat y) {
    return vec3(x, y, 0.0f);
}

GLfloat magnitude(vector4_t vec) {
    return dot(vec, vec);
}

GLfloat sqrMagnitude(vector4_t vec) {
    return sqrtf(magnitude(vec));
}

GLfloat dot(vector4_t a, vector4_t b) {
    GLfloat res = 0;
    for (int i = 0; i < 4; i++) {
        res += a.matrix[i] * b.matrix[i];
    }

    return res;
}

GLfloat angle(vector4_t from, vector4_t to) {
    return dot(from, to) / (sqrMagnitude(from) * sqrMagnitude(to));
}

vector4_t clampMagnitude(vector4_t vec, GLfloat radius) {
    GLfloat k = radius / sqrMagnitude(vec);
    return mulVector(vec, k);
}

vector4_t cross3(vector4_t a, vector4_t b) {
    return vec3(
            *a.y * *b.z - *a.z * *b.y,
            *a.x * *b.z - *a.z * *b.x,
            *a.x * *b.y - *a.y * *b.x
    );
}

vector4_t addVector(vector4_t a, vector4_t b) {
    vector4_t res = ZERO_VECTOR;
    for (int i = 0; i < 4; i++) {
        res.matrix[i] = a.matrix[i] + b.matrix[i];
    }

    return res;
}

vector4_t subVector(vector4_t a, vector4_t b) {
    vector4_t res = ZERO_VECTOR;
    for (int i = 0; i < 4; i++) {
        res.matrix[i] = a.matrix[i] - b.matrix[i];
    }

    return res;
}

vector4_t mulVector(vector4_t vec, GLfloat k) {
    vector4_t res = ZERO_VECTOR;
    for (int i = 0; i < 4; i++) {
        res.matrix[i] = vec.matrix[i] * k;
    }

    return res;
}

vector4_t divVector(vector4_t vec, GLfloat k) {
    return mulVector(vec, 1 / k);
}

bool equals(vector4_t a, vector4_t b) {
    bool flag = true;
    for (int i = 0; i < 4; i++) {
        flag &= fabsf(a.matrix[i] - b.matrix[i]) < EQUALS_ACCURACY;
    }
    return flag;
}

