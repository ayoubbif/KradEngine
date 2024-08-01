#version 460 core

// Output
out vec4 FragColor;

// Input the color from vertex shader
in vec3 color;

// Input the texture coordinate from vertex shader
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord);
}
