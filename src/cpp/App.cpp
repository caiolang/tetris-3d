#include "App.h"

#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLSLProgram.h>
#include <Model.h>

// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

/* Model and Shader variables */
GLSLProgram *shader;
Model *cube;

void framebuffer_size_callback(GLFWwindow*, int new_screen_width, int new_screen_height)
{
    glViewport(0, 0, new_screen_width, new_screen_height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check for ESC key
        glfwSetWindowShouldClose(window, true);
}

    /* Shader setup */
GLSLProgram* setupShader(const char* shaderVSSource, const char* shaderFSSource)
{
    GLSLProgram* shaderProgram = new GLSLProgram();

    if(!shaderProgram->compileShaderFromFile(shaderVSSource, GL_VERTEX_SHADER))
    {
        printf("Vertex shader failed to compile! %s\n", shaderProgram->log().c_str());
        delete shaderProgram;
        exit(1);
    }

    if (!shaderProgram->compileShaderFromFile(shaderFSSource, GL_FRAGMENT_SHADER))
    {
        printf("Fragment shader failed to compile! %s\n", shaderProgram->log().c_str());
        delete shaderProgram;
        exit(1);
    }

    if (!shaderProgram->link())
    {
        printf("Shader program failed to link! %s\n", shaderProgram->log().c_str());
        delete shaderProgram;
        exit(1);
    }

    shaderProgram->printActiveUniforms();
    shaderProgram->printActiveAttribs();

    return shaderProgram;
}


int main()
{
    GLFWwindow* window;

    /* GLFW : Init and Configuration */
    if (!glfwInit())
        exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* GLFW : Creating Window */
    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    /* Glew */
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        exit(1);

    /* Model and Shader config */
    shader = setupShader("src/glsl/cube.vs", "src/glsl/cube.fs");
    cube = new Model("assets/models/cube.obj");

    /* Setting clear color */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    /* Render Loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // Clearing the collor buffer

        shader->use();
        cube->draw();

        processInput(window); // Check for inputs

        /* Swap buffers, check and call events */
        glfwSwapBuffers(window); // Swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window
        glfwPollEvents(); // Checks if any events are triggered (keyboard/mouse), updates the window state, and calls the corresponding functions
    }

    exit(0);
}
