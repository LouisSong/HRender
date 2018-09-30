#ifndef SHADER_H
#define SHADER_H

#include<glad\glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const GLchar* vertexPath,const GLchar* fragmentPath);
	void use();
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name,float value);
	void Shader::SetVector3(const std::string &name, float x, float y, float z);
	void Shader::SetVector4(const std::string &name, float x, float y, float z, float w);
	~Shader();
};

#endif