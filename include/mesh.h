#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"camera.h"
#include"texture.h" // cf my little drawing

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Stores VAO in public so it can be used in the Draw function
	VAO meshVAO;

	// Init and draw
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void Draw(Shader& shader, Camera& camera);
};
#endif
