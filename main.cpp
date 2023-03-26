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
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
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
    VAO1.LinkVBO(VBO1, 0);
    // Unbiinding all the buffers
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Main loop
    while (!glfwWindowShouldClose(window)) 
    {
        //Background color
        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL to use the shader program
        shaderProgram.Activate();
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