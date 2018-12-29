#ifndef MODLE_H
#define MODLE_H

#include "Shader.h"
#include "Mesh.h"
#include "Res.h"
#include<vector>
#include<assimp\Importer.hpp>
#include<assimp\scene.h>
#include<assimp\postprocess.h>

class Model
{
public:
	std::vector<Mesh> meshes;

	Model(char *path);
	void Draw(Shader shader);
	~Model();
private:
	
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType textureType);
};
#endif