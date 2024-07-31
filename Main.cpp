#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex shader source code
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.5f, 0.4f, 1.0f);\n"
"}\0";

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

	// Compile the vertex and fragment shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create a shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	
	// Link the shader program
	glLinkProgram(shaderProgram);

	// Delete the shaders as they are linked to the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
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

	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1, // Upper triangle
	};


	// Create a vertex array object and vertex buffer object 
	GLuint VAO, VBO, EBO;

	// Generate the vertex array object and vertex and element buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// Bind the vertex array object and vertex buffer object
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copy the vertices to the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind the vertex array object and vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Set the background color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// Clear the color buffer and assign the background color
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the front and back buffers
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program
		glUseProgram(shaderProgram);

		// Bind the vertex array object
		glBindVertexArray(VAO);

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Delete the vertex array object, vertex buffer object, and shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
