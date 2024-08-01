#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices of the triangle
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom left
	 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom right
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // top
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	 0.0f,  -0.5f * float(sqrt(3)) / 3, 0.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1, // Upper triangle
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
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
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
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader program
		shaderProgram.Activate();

		// Bind the VAO
		VAO1.Bind();

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Delete the vertex array object, vertex buffer object, and shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
