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

#include "include/shaderClass.h"
#include "include/mesh.h"
#include "include/model.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

//------------------------------------------------------------------------------------------------------------------------------------//

Vertex vertices[] =
{ //     COORDINATES                           /        COLORS                  /    Normals                        /        tex coord       //
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f), 	 glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(0.0f, 0.0f)},// Bottom side
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(0.0f, 5.0f)},     
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(5.0f, 5.0f)}, 
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, -1.0f, 0.0f),       glm::vec2(5.0f, 0.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f), 	 glm::vec3(-0.8f, 0.5f,  0.0f),      glm::vec2(0.0f, 0.0f)},// Left Side
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(-0.8f, 0.5f,  0.0f),      glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f),      glm::vec3(0.92f, 0.86f, 0.76f),	 glm::vec3(-0.8f, 0.5f,  0.0f),      glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, 0.5f, -0.8f),       glm::vec2(5.0f, 0.0f)},// Non-facing side
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, 0.5f, -0.8f),       glm::vec2(0.0f, 0.0f)},  
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f),      glm::vec3(0.92f, 0.86f, 0.76f),	 glm::vec3(0.0f, 0.5f, -0.8f),       glm::vec2(2.5f, 5.0f)},  

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.8f, 0.5f,  0.0f),       glm::vec2(0.0f, 0.0f)}, // Right side
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.8f, 0.5f,  0.0f),       glm::vec2(5.0f, 0.0f)}, 
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f),      glm::vec3(0.92f, 0.86f, 0.76f),	 glm::vec3(0.8f, 0.5f,  0.0f),       glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(0.5f, 0.0f,  0.5f),      glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec3(0.0f, 0.5f,  0.8f),       glm::vec2(5.0f, 0.0f)}, // Facing side
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f), 	 glm::vec3(0.0f, 0.5f,  0.8f),       glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f),      glm::vec3(0.92f, 0.86f, 0.76f),	 glm::vec3(0.0f, 0.5f,  0.8f),       glm::vec2(2.5f, 5.0f)}  
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side 
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

//------------------------------------------------------------------------------------------------------------------------------------//

Vertex islandVertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};

GLuint islandIndices[] =
{
	0, 1, 2,
	0, 2, 3,
};

//------------------------------------------------------------------------------------------------------------------------------------//

int main(){

    // Initialize GLFW
    glfwInit();

    // Set the version of OpenGL we want to use = 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // profile = package of functions, here we choose core profile since we want to work with modern functions

    // Create the window we want, in this case a 1920x1080 window
    GLFWwindow* window = glfwCreateWindow(width, height, "Volcano Project", NULL, NULL);
    
    // If there is an error in creating the window, we terminate the program
    if (window == NULL){
        std::cout << "Failed to create the window" << std::endl;
        glfwTerminate();
        return -1;
    } 

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load glad
    gladLoadGL();

    glViewport(0, 0, width, height); // The area of the window we want OpenGl to render in from (0,0) to (1920,1080)

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Texture

    Texture textures[]{
        Texture("rock.jpg", "diffuse", 0)
    };

	Texture islandTextures[]{
		Texture("grass.jpg", "diffuse", 0)
	};

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Volcano Mesh

    // Create shader program
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    // Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create volcano mesh
	Mesh volcano(verts, ind, tex);

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Ambiant light Mesh

    Shader lightShader("shaders/light.vert", "shaders/light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Crate light mesh
	Mesh light(lightVerts, lightInd, tex);



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);



	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//------------------------------------------------------------------------------------------------------------------------------------//

    // Island Mesh
	std::vector <Vertex> islandVerts(islandVertices, islandVertices + sizeof(islandVertices) / sizeof(Vertex));
	std::vector <GLuint> islandInd(islandIndices, islandIndices + sizeof(islandIndices) / sizeof(GLuint));
	std::vector <Texture> islandTex(islandTextures, islandTextures + sizeof(islandTextures) / sizeof(Texture));

	Mesh island(islandVerts, islandInd, islandTex);

    //------------------------------------------------------------------------------------------------------------------------------------//

    glEnable(GL_DEPTH_TEST); // Enable the Depth Buffer, allows us to see objects in front of others 

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Camera

    Camera camera(width, height, glm::vec3(0.0f, 0.5f, 2.0f));

    //------------------------------------------------------------------------------------------------------------------------------------//

	// Model

	// Model model("modeles/test/scene.gltf");

	//------------------------------------------------------------------------------------------------------------------------------------//

    // Print in the console the keys we can use and their functions
    std::cout << "Press ESC to exit" << std::endl;
    std::cout << "Press Z to move forward" << std::endl;  
    std::cout << "Press S to move backward" << std::endl;
    std::cout << "Press Q to move left" << std::endl;
    std::cout << "Press D to move right" << std::endl;
    std::cout << "Press space to move up" << std::endl;
    std::cout << "Press left ctrl to move down" << std::endl;
    std::cout << "Press left mouse button to move the camera" << std::endl;

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Main loop
    while (!glfwWindowShouldClose(window)) 
    {
        //Background color (i want to make it sky blue)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draws different meshes
		volcano.Draw(shaderProgram, camera);
		island.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		// model.Draw(shaderProgram, camera);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //------------------------------------------------------------------------------------------------------------------------------------//

    // Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
