#include "Font.h"
#include<iostream>

Font::Font(std::string path)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FT INIT ERROR!" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		std::cout << "ERROR::Failed to load font!" << std::endl;

	//指定字符表
	FT_Select_Charmap(face,FT_ENCODING_UNICODE);
	//设置字符的高度，宽度自适应
	FT_Set_Pixel_Sizes(face, 0, 24);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//Disable byte-alignment restriction

	for (size_t i = 0; i < 128; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "ERROR:load character faild.c=" << i << std::endl;
			continue;
		}
			
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		CharacterMap.insert(std::pair<GLchar, Character>(i, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//Font vao vbo
	glGenVertexArrays(1, &fontVAO);
	glGenBuffers(1, &fontVBO);
	glBindVertexArray(fontVAO);
	glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Font::RenderText(glm::mat4 projection, Shader & shader, std::string text, GLfloat posX, GLfloat posY, GLfloat scale, glm::vec3 color)
{
	shader.use();
	shader.SetMatrix4("projection", projection);
	shader.SetVector3("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(fontVAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character character = CharacterMap[*c];
		GLfloat x = posX + character.Bearing.x * scale;
		GLfloat y = posY - (character.Size.y - character.Bearing.y) * scale;

		GLfloat w = character.Size.x * scale;
		GLfloat h = character.Size.y * scale;

		GLfloat vertices[6][4] = {
			{ x,y + h,		0.0,0.0 },
			{ x,y,			0.0,1.0 },
			{ x + w,y,		1.0,1.0 },

			{ x,y + h,		0.0,0.0 },
			{ x + w,y,		1.0,1.0 },
			{ x + w,y + h,	1.0,0.0 },
		};

		glBindTexture(GL_TEXTURE_2D, character.TextuerID);
		glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		posX += (character.Advance >> 6) * scale;//advance is number of 1/64 pixels
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
