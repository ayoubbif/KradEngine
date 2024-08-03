#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices of the triangle
GLfloat vertices[] =
{	//		COORDINATES	   /		COLORS	  /   Tex Coordinates //				  		
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-0.5f,	0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Lower left triangle
	0, 3, 2, // Lower right triangle
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Set GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 800, "KradEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Load OpenGL functions
	gladLoadGL();

	// Set the viewport
	glViewport(0, 0, 800, 800);

	// Generate shader program using default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate vertex array object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Generate VBO and link it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate EBO and link it to indices
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Get the uniform variable from the vertex shader
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture wood("wood.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

	wood.texUnit(shaderProgram, "tex0", GL_TEXTURE0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader program
		shaderProgram.Activate();

		// Set the uniform variable
		glUniform1f(uniID, 0.5f);

		// Bind the texture
		wood.Bind();

		// Bind the VAO
		VAO1.Bind();

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Delete the vertex array object, vertex buffer object, texture, and shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	wood.Delete();
	shaderProgram.Delete();

	// Delete the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
