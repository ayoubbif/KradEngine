#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assign the type of texture to the object
	type = texType;

	// Store the width, height, and the number of color channels of the image
	int width, height, nrChannels;

	// Flip the image vertically
	stbi_set_flip_vertically_on_load(true);

	// Read the image from the file
	unsigned char* bytes = stbi_load(image, &width, &height, &nrChannels, 0);

	// Generate a texture
	glGenTextures(1, &ID);

	// Assign the texture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configure the algorithm to use when the texture is scaled
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set the texture wrapping parameters
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Assign the image to the texture
	glTexImage2D(texType, 0, GL_RGB, width, height, 0, format, pixelType, bytes);

	// Generate mipmaps
	glGenerateMipmap(texType);

	// Free the image memory
	stbi_image_free(bytes);

	// Unbind the texture
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Get the location of the uniform variable
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// Activate the shader program
	shader.Activate();

	// Assign the texture unit to the uniform variable
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

