#ifndef MESH_H
#define MESH_H
#include<glm.hpp>
#include<string>
#include<vector>
#include "Shader.h"

enum TextureType
{
	Diffuse,
	Specular,
	Normal,
	Height
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	TextureType type;
	std::string path;
};



class Mesh
{
public:
	unsigned int VAO;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader shader);
	std::string TextureTypeToString(TextureType type);

	Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
	~Mesh();
private:
	unsigned int VBO, EBO;
	void setupMesh();
};
#endif