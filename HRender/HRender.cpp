// HRender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <math.h>
#include "Shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main();
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 512;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HRender", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "create window failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "gald failed!" << std::endl;
		return -1;
	}

	Shader simpleShader("s.vs","s.fs");

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,1,1,// top right
		0.5f, -0.5f, 0.0f,  1.0f,1.0f,1.0f,1,0,// bottom right
		-0.5f, -0.5f, 0.0f,  1.0f,0.0f,0.0f,0,0,// bottom left
		-0.5f,  0.5f, 0.0f,   0.0f,0.0f,0.0f,0,1// top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#pragma region loadTexture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load texture failed!" << std::endl;
	}
	stbi_image_free(data);
#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制线条模式
		//glPolygonMode(GL_BACK, GL_LINE);
		glClearColor(0.1f, 0.25f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = (float)glfwGetTime();
		float greenValue = ((sin(timeValue)) / 2.0f) + 0.5f;
		greenValue = 1;
		simpleShader.use();
		simpleShader.SetVector4("uColor", 1, greenValue,1, 1.0f);
		glBindVertexArray(VAO);

		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
    return 0;
}

int drawMode = 0;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE)
	{
		
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_M && action == GLFW_RELEASE)
	{
		drawMode++;
		if ((drawMode & 1) == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制线条模式
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//绘填充模式
	}
}


