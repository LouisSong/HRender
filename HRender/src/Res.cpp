#include "stdafx.h"
#include "Res.h"

Texture Res::loadTexture(const GLchar * path, TextureType type)
{
	for (unsigned int i = 0; i < textures_loaded.size(); i++)
	{
		if (std::strcmp(textures_loaded[i].path.data(), path) == 0)
			return textures_loaded[i];
	}

	Texture texture;
	texture.id = loadTextureFromFile(path);
	texture.type = type;
	texture.path = path;

	textures_loaded.push_back(texture);

	return texture;
}

unsigned int x = 0;

unsigned int Res::loadTextureFromFile(const GLchar * texturePath)
{
	std::cout << texturePath << std::endl;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "load texture failed!" << texturePath << std::endl;
	}
	stbi_image_free(data);

	return textureID;// textureID;
}

std::vector<Texture> Res::textures_loaded;