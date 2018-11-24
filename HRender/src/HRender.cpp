// HRender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <math.h>
#include "Shader.h"
#include "Camera.h"
#include "PointLight.h"
#include "Res.h"
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
int main();
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 512;

int drawMode = 0;
double lastTime = 0;
float delta = 0;

Camera* camera;

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
	glfwSetCursorPosCallback(window,mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "gald failed!" << std::endl;
		return -1;
	}

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	//Shader lampShader("LampShader.vs", "LampShader.fs");
	Shader lightShader("Resource/Shaders/Light.vs", "Resource/Shaders/Light.fs");
	Shader depthShader("Resource/Shaders/Depth.vs", "Resource/Shaders/Depth.fs");
	Shader singleColorShader("Resource/Shaders/SingleColor.vs", "Resource/Shaders/SingleColor.fs");
	Shader simpleShader("Resource/Shaders/simple.vs", "Resource/Shaders/simple.fs");

	//unsigned int zhenji256 = Res::loadTextureFromFile("glass_dif.png");
	//unsigned int specularMap = Res::loadTextureFromFile("container2_specular.png");
	//unsigned int texture2 = Res::loadTextureFromFile("headicon.png");
	unsigned int cubeTexture = Res::loadTextureFromFile("Resource/Textures/marble.jpg");
	unsigned int floorTexutre = Res::loadTextureFromFile("Resource/Textures/metal.png");
	unsigned int grassTexutre = Res::loadTextureFromFile("Resource/Textures/blending_transparent_window.png");
	unsigned int zhenjiTexutre = Res::loadTextureFromFile("Resource/Models/zhenji/zhenji256.png");
	
#pragma region InitCamera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	camera = new Camera(cameraPos, cameraTarget, cameraUp);
#pragma endregion

#pragma region InitLights
	std::vector<PointLight*> pointLights;
	for (int i = 0; i < 4; i++)
	{
		pointLights.push_back(new PointLight());
	}

	//pointLight 0
	PointLight* pointLight = pointLights[0];
	pointLight->position = glm::vec3(2, 1, 0);
	pointLight->constant = 1.0f;
	pointLight->linear = 0.09f;
	pointLight->quadratic = 0.032f;
	pointLight->ambient = glm::vec3(0.3, 0.3, 0.3);
	pointLight->diffuse = glm::vec3(0, 1, 0);
	pointLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);

	//pointLight 1
	pointLight = pointLights[1];
	pointLight->position = glm::vec3(0, 1, -2);
	pointLight->constant = 1.0f;
	pointLight->linear = 0.09f;
	pointLight->quadratic = 0.032f;
	pointLight->ambient = glm::vec3(0.3, 0.3, 0.3);
	pointLight->diffuse = glm::vec3(1, 0, 0);
	pointLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);

	//pointLight 2
	pointLight = pointLights[2];
	pointLight->position = glm::vec3(0, 1, 2);
	pointLight->constant = 1.0f;
	pointLight->linear = 0.09f;
	pointLight->quadratic = 0.032f;
	pointLight->ambient = glm::vec3(0.3, 0.3, 0.3);
	pointLight->diffuse = glm::vec3(0, 0, 1);
	pointLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);

	//pointLight 3
	pointLight = pointLights[3];
	pointLight->position = glm::vec3(-2, 1, 0);
	pointLight->constant = 1.0f;
	pointLight->linear = 0.09f;
	pointLight->quadratic = 0.032f;
	pointLight->ambient = glm::vec3(0.3, 0.3, 0.3);
	pointLight->diffuse = glm::vec3(1, 1, 0);
	pointLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);
#pragma endregion

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	std::vector<glm::vec3> grassPositions;
	grassPositions.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	grassPositions.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
	grassPositions.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	grassPositions.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	grassPositions.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	

	float grassVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	// plane VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	//grass vao
	unsigned int grassVAO, grassVBO;
	glGenVertexArrays(1, &grassVAO);
	glGenBuffers(1, &grassVBO);
	glBindVertexArray(grassVAO);
	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grassVertices), &grassVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glBindVertexArray(0);

	//Model yuqiang("nanosuit/nanosuit.xyz");
	Model zhenji("Resource/Models/zhenji/ZhenJi.xyz");
	//Model gameModel("Resource/Models/.FBX");

	depthShader.use();
	depthShader.setInt("texture1", 0);

	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		delta = (float)(now - lastTime);
		lastTime = now;

		processInput(window);
		//camera->UpdateVectors();
		camera->UpdatePosition();
		camera->UpdateViewMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制线条模式
		//glPolygonMode(GL_BACK, GL_LINE);
		glClearColor(0.1f, 0.25f, 0.25f, 0.0f);

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		glStencilMask(0x00);//绘制地面不更新stencil buffer
		
		simpleShader.use();

		glm::mat4 view = camera->view;
		glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float)(SCR_WIDTH / SCR_HEIGHT), 1.1f, 100.0f);

		simpleShader.SetMatrix4("view", view);
		simpleShader.SetMatrix4("projection", projection);

		//floor
		glm::mat4 model = glm::mat4();
		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexutre);
		simpleShader.SetMatrix4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		//cube1
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-1.0f, 0.1f, -1.0f));
		simpleShader.SetMatrix4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//cube2
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.1f, 0.0f));
		simpleShader.SetMatrix4("model", model);
		//glBindTexture(GL_TEXTURE0, zhenjiTexutre);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		//甄姬
		lightShader.use();
		lightShader.SetMatrix4("view", view);
		lightShader.SetMatrix4("projection", projection);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		lightShader.SetMatrix4("model", model);
		glBindTexture(GL_TEXTURE_2D, zhenjiTexutre);

		//simpleShader.use();
		zhenji.Draw(simpleShader);

		//grass
		simpleShader.use();
		glBindVertexArray(grassVAO);
		glBindTexture(GL_TEXTURE_2D, grassTexutre);
		glActiveTexture(GL_TEXTURE0);
		for (int i = 0; i < grassPositions.size(); i++)
		{
			model = glm::mat4();
			model = glm::translate(model, grassPositions[i]);
			simpleShader.SetMatrix4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glBindVertexArray(0);
		
		//绘制cube，更新stencil buffer
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		lightShader.SetMatrix4("model", model);
		glBindTexture(GL_TEXTURE_2D, zhenjiTexutre);
		//gameModel.Draw(simpleShader);

		//绘制描边
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilMask(0x00);
		//glDisable(GL_DEPTH_TEST);

		//singleColorShader.use();
		//singleColorShader.SetMatrix4("view", view);
		//singleColorShader.SetMatrix4("projection", projection);

		////cube1 out line
		//glBindVertexArray(cubeVAO);

		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(-1.0f, 0.1f, -1.0f));
		//model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//singleColorShader.SetMatrix4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		////cube2 out line
		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(2.0f, 0.1f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//singleColorShader.SetMatrix4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		////甄姬 outline
		//glBindVertexArray(0);

		////甄姬
		//
		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.01f, 1.01f, 1.01f));
		//model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//singleColorShader.SetMatrix4("model", model);

		//zhenji.Draw(singleColorShader);

		glBindVertexArray(0);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
	//
		

		//========================= 绘制灯光物件 ===========================


#pragma region dirLight
//		glm::vec3 lightPos(5.0f, 5.0f, 0.0f);
//
//		glm::mat4 model;
//		model = glm::translate(model, lightPos);
//		model = glm::scale(model, glm::vec3(0.2f));
//
//		lampShader.use();
//		lampShader.SetMatrix4("model", model);
//		lampShader.SetMatrix4("view", view);
//		lampShader.SetMatrix4("projection", projection);
//
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);		
//#pragma endregion
//
//#pragma region pointLights
//		for (int i = 0; i < 4; i++)
//		{
//			glm::mat4 model;
//			model = glm::translate(model, (*pointLights[i]).position);
//			model = glm::scale(model, glm::vec3(0.2f));
//			lampShader.SetMatrix4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		glBindVertexArray(0);
#pragma endregion

		//========================== 绘制方块 =====================================

		/*lightShader.use();
		lightShader.setFloat("material.shininess", 32.0f);

		lightShader.SetVector3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightShader.SetVector3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightShader.SetVector3("light.specular", 1.0f, 1.0f, 1.0f);
		lightShader.SetVector3("light.position", lightPos);
		lightShader.SetVector3("viewPos", camera->pos);*/

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		//for (int i = 0; i < 4; i++)
		//{
		//	(*pointLights[i]).Prepare(&lightShader, i);
		//}
		//
		//model = glm::mat4();
		////model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.15f));
		//model = glm::translate(model,glm::vec3(0,0.0f,0));


		//glm::mat4 normalModel;
		//normalModel = glm::mat3(glm::transpose(glm::inverse(normalModel)));

		//lightShader.SetMatrix3("normalModel",normalModel);

		//lightShader.SetMatrix4("model", model);
		//lightShader.SetMatrix4("view", camera->view);
		//lightShader.SetMatrix4("projection", projection);

		//yuqiang.Draw(lightShader);

		

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, specularMap);

		//glBindVertexArray(lightVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		//simpleShader.setInt("texture1", 0);
		//simpleShader.setInt("texture2", 1);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &lightVAO);

	glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->Move(FORWARD, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->Move(LEFT, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->Move(BACKWARD, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->Move(RIGHT, delta);
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

double lastX, lastY;
bool isFirstMouseIn = true;
bool isPressedMouseButton = false;

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{

	if (isPressedMouseButton == false)
	{
		lastX = xpos;
		lastY = ypos;
	}
	else
	{
		if (isFirstMouseIn)
		{
			isFirstMouseIn = false;
			lastX = xpos;//SCR_WIDTH >> 1;
			lastY = ypos;//SCR_HEIGHT >> 1;
			//camera->yaw = -90;
		}

		float xoffset = (float)(xpos - lastX);
		float yoffset = (float)(ypos - lastY);
		lastX = xpos;
		lastY = ypos;
		//std::cout << "位移：" << xoffset << "," << yoffset << std::endl;
		camera->MouseMove(xoffset, yoffset);
	}
	
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera->Zoom((float)yoffset);
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
	{

		isPressedMouseButton = true;
	}
	else if(action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		isPressedMouseButton = false;
	}
}

