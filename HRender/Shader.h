#ifndef SHADER_H
#define SHADER_H

#include<glad\glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm.hpp>
#include<gtc\type_ptr.hpp>

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
	void Shader::SetVector3(const std::string &name, glm::vec3 value);

	void Shader::SetVector4(const std::string &name, float x, float y, float z, float w);
	void Shader::SetMatrix3(const std::string &name, const glm::mat3 matrix);
	void Shader::SetMatrix4(const std::string &name, const glm::mat4 matrix);
	~Shader();
};

#endif