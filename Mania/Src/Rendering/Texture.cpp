#include "Texture.h"
#include <GL\glew.h>
#include "../StaticLibs/stb_image.h"

Texture create_texture(const char * textureFile)
{
	int32 width, height;
	const unsigned char* pPixels = stbi_load(textureFile, &width, &height, NULL, 4);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
