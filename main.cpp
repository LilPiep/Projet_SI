#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "include/glad/glad.h"
#include <math.h>

#include "include/VBO.h"
#include "include/VAO.h"
#include "include/shaderClass.h"
#include "include/EBO.h"

// Verices coordinates
    GLfloat vertices[] = {
        // Positions          // Colors
        -0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f, 0.0f,
        0.5f,   -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.6f, 0.1f,
        0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f,   1.0f, 0.5f, 0.3f,
        -0.25f, 0.5f * float(sqrt(3)) / 6,      0.0f,   0.7f, 0.5f, 0.3f,
        0.25f,  0.5f * float(sqrt(3)) / 6,      0.0f,   0.8f, 0.4f, 0.15f,
        0.0f,   -0.5f * float(sqrt(3)) / 3,     0.0f,   0.9f, 0.3f, 0.2f
    };

    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

int main(){

    // Initialize GLFW
    glfwInit();

    // Set the version of OpenGL we want to use = 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // profile = package of functions, here we choose core profile since we want to work with modern functions

    GLFWwindow* window = glfwCreateWindow(800, 800, "Volcano Project", NULL, NULL);
    
    // If there is an error in creating the window, we terminate the program
    if (window == NULL){
        std::cout << "Failed to create the window" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

    //Init glad
    gladLoadGL();

    glViewport(0, 0, 800, 800); // The area of the window we want OpenGl to render in from (0,0) to (800,800)

    // Create shader program
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    // Create VAO
    VAO VAO1;
    VAO1.Bind();

    // Create VBO
    VBO VBO1(vertices, sizeof(vertices));
    
    // Create EBO
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Unbiinding all the buffers
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Main loop
    while (!glfwWindowShouldClose(window)) 
    {
        //Background color
        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL to use the shader program
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f); // Very important to type this AFTER shaderProgram.Activate()
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}