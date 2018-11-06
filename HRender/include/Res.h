#ifndef RES_H
#define RES_H
#include "stb_image.h"
#include "Model.h"
#include <glad\glad.h>
#include <iostream>

class Res
{
	public:
		static std::vector<Texture> textures_loaded;
		static unsigned int loadTextureFromFile(const GLchar* texturePath);
		static Texture loadTexture(const GLchar* path, TextureType type);

		//Res(static std::vector<Texture> _textures_loaded) :textures_loaded(_textures_loaded) {};
};
#endif