#pragma once
#include<GL/glew.h>
#include<fstream>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<iostream>
class Textures
{
public:
	static unsigned int load2DTexture(const char* TexturePath, GLint internalFormat, GLenum format, int textureSlot) {
		unsigned int textureID = 0;
		int width, height, nrChannel;
		stbi_set_flip_vertically_on_load(true);
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, textureID);
		unsigned char* data = stbi_load(TexturePath, &width, &height, &nrChannel, 0);
		if (nrChannel == 3)
		{
			internalFormat == GL_RGB;
			format = GL_RGB;
		}
		else if (nrChannel == 4)
		{
			internalFormat == GL_RGBA;
			format = GL_RGBA;
		}
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Load image failed" << std::endl;
		}
		stbi_image_free(data);
		return textureID;
	}
};

