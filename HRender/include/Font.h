#ifndef FONT_H
#define FONT_H
#include<glad\glad.h>
#include<glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include<string>
#include<map>
#include "Shader.h"

struct Character
{
	GLuint TextuerID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class Font
{
public:
	Font(std::string path);
	void RenderText(glm::mat4 projection, Shader &shader, std::string text, GLfloat posX, GLfloat posY,
		GLfloat scale, glm::vec3 color);
private:
	std::map<GLchar, Character> CharacterMap;
	unsigned int fontVAO, fontVBO;
};
#endif