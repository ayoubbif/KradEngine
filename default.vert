#version 460 core

// Coordinates of the vertex
layout (location = 0) in vec3 aPos;

// Colors of the vertex
layout (location = 1) in vec3 aColor;

// Texture coordinates of the vertex
layout (location = 2) in vec2 aTex;

// Output the color to the fragment shader
out vec3 color;

// Output the texture coordinates to the fragment shader
out vec2 texCoord;

// Conrtol the scale of the vertex
uniform float scale;

void main()
{
	// Scale the position of the vertex
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	
	// Pass the color to the fragment shader
	color = aColor;

	// Pass the texture coordinates to the fragment shader
	texCoord = aTex;
}
