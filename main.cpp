#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "include/glad/glad.h"
#include <math.h>
#include "include/stb/stb_image.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "include/VBO.h"
#include "include/VAO.h"
#include "include/shaderClass.h"
#include "include/EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Verices coordinates
    GLfloat vertices[] = {
        // Positions                 // Colors              // Texture Coords
        -0.5f,   0.0f,    0.5f,    0.83f, 0.70f, 0.44f,     0.0f, 0.0f, 
        -0.5f,   0.0f,    -0.5f,   0.83f, 0.70f, 0.44f,     5.0f, 0.0f, 
        0.5f,    0.0f,    -0.5f,   0.83f, 0.70f, 0.44f,     0.0f, 0.0f, 
        0.5f,    0.0f,    0.5f,    0.83f, 0.70f, 0.44f,     5.0f, 0.0f,
        0.0f,    0.8f,    0.0f,    0.92f, 0.86f, 0.76f,     2.5f, 5.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

int main(){

    // Initialize GLFW
    glfwInit();

    // Set the version of OpenGL we want to use = 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // profile = package of functions, here we choose core profile since we want to work with modern functions

    GLFWwindow* window = glfwCreateWindow(width, height, "Volcano Project", NULL, NULL);
    
    // If there is an error in creating the window, we terminate the program
    if (window == NULL){
        std::cout << "Failed to create the window" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

    //Init glad
    gladLoadGL();

    glViewport(0, 0, width, height); // The area of the window we want OpenGl to render in from (0,0) to (800,800)

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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbiinding all the buffers
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("shrek.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0Uni, 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    // Main loop
    while (!glfwWindowShouldClose(window)) 
    {
        //Background color
        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL to use the shader program
        shaderProgram.Activate();

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >=  1 / 60){
            rotation += 0.5f;
            prevTime = crntTime;
        }

        glm::mat4 model = glm::mat4(1.0f); // Identity matrixes
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(width/height), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); 
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj)); 

        glUniform1f(uniID, 0.5f); // Very important to type this AFTER shaderProgram.Activate()
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    glDeleteTextures(1, &texture);
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}