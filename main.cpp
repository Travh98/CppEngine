#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

int main() 
{
	glfwInit();
	std::cout << "Hello world!" << std::endl;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// normal floats might differ from the size of floats that OpenGL uses
	GLfloat vertices[] =
	{
		-0.5,		-0.5 * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f,	// lower left corner
		0.5,		-0.5 * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f,	// lower right corner
		0.0,		0.5 * float(sqrt(3)) * 2 / 3,	0.0f,	1.0f, 0.6f, 0.32f,	// upper corner
		-0.25f,		0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// inner left
		0.25f,		0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// inner right
		0.0f,		-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f	// inner down
	};

	GLuint indices[] =
	{
		0, 3, 5,  // lower left triangle
		3, 2, 4,  // lower right triangle
		5, 4, 1,  // upper triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Youtube OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to make new glfw window" << std::endl;
	}

	// Context is a sort of object that holds the whole of OpenGL
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices));
	EBO ebo1(indices, sizeof(indices));

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	// Uniforms
	GLuint uniID = glGetUniformLocation(shaderProgram.id, "scale");

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Swap the back buffer with the main buffer
	glfwSwapBuffers(window);


	// Loop while polling until you close the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}