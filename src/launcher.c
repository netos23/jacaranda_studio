// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>

// Include GLEW
#include "GL/glew.h"

// Include GLFW
#include "GLFW/glfw3.h"

#include "core/shader.h"
#include "math/matrix.h"
#include "math/math.h"

GLFWwindow *mainWindow;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);


int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    // Setup window
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    mainWindow = glfwCreateWindow(1024, 768, "Cube", NULL, NULL);
    if (mainWindow == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. "
                "Try the 2.1 version of the opengl.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mainWindow);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(mainWindow, key_callback);

    // Set viewport
    int viewportWidth, viewPortHeight;
    glfwGetFramebufferSize(mainWindow, &viewportWidth, &viewPortHeight);
    glViewport(0, 0, viewportWidth, viewPortHeight);

    glEnable(GL_DEPTH_TEST);

    GLuint shader = loadShader("src/shaders/vertex.shader",
                               "src/shaders/fragment.shader");


    // Set up vertex data (and buffer(s)) and attribute pointers
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    vector4_t cubePositions[] = {
            vec3(0.0f, 0.0f, 0.0f),
            vec3(2.0f, 5.0f, -15.0f),
            vec3(-1.5f, -2.2f, -2.5f),
            vec3(-3.8f, -2.0f, -12.3f),
            vec3(2.4f, -0.4f, -3.5f),
            vec3(-1.7f, 3.0f, -7.5f),
            vec3(1.3f, -2.0f, -2.5f),
            vec3(1.5f, 2.0f, -2.5f),
            vec3(1.5f, 0.2f, -1.5f),
            vec3(-1.3f, 1.0f, -1.5f)
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // load and create a texture
    // -------------------------
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint width, height;
    GLubyte *image = SOIL_load_image("assets/container.jpg", &width, &height,
                                     0, SOIL_LOAD_RGB);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    do {
        glfwPollEvents();
        // Clear the screen.
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader);

        // Create transformations

        matrix4_t view = oneMatrix();
        matrix4_t projection;


        // view = rotate(view, (GLfloat) glfwGetTime() * rad(5), vec3(0.f, 1.f, 0.f));
        view = translate(view, vec3(0.0f, 0.0f, -5.0f));
        projection = persp(45.f, (GLfloat) viewportWidth / (GLfloat) viewPortHeight,
                            0.1f, 100.0f);


        // Get matrix's uniform location and set matrix
        GLint modelLoc = glGetUniformLocation(shader, "model");
        GLint viewLoc = glGetUniformLocation(shader, "view");
        GLint projectionLoc = glGetUniformLocation(shader, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);
        glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);

        glBindVertexArray(VAO);


        for (int i = 0; i < 10; i++) {
            matrix4_t model = oneMatrix();
            model = translate(model, cubePositions[i]);
            if (i % 2 == 0) {
                model = rotate(model, (GLfloat) glfwGetTime() * rad(55.0f),
                               vec3(0.1f * (GLfloat) i, 0.1f * (GLfloat) i, 0.1f * (GLfloat) i));
            } else {
                model = rotate(model, (GLfloat) i * rad(20.0f),
                               vec3(0.5f, 1.0f, 0.0f));
            }
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            freeMatrix(model);
        }
        glBindVertexArray(0);

        freeMatrix(view);
        freeMatrix(projection);
        // Swap buffers
        glfwSwapBuffers(mainWindow);

    } while (!glfwWindowShouldClose(mainWindow));

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // Check if the ESC key was pressed or the window was closed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}
