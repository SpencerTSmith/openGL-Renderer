#include "texture.h"

#include <iostream>

#include "utilities/stb_image.h"


loglr::texture::texture(const std::string& texture_path, GLuint pixel_format) {
	stbi_set_flip_vertically_on_load(true);
	int32_t width, height, num_channels;
	GLubyte* tex_data = stbi_load(texture_path.c_str(), &width, &height, &num_channels, 0);
	if (!tex_data) {
		std::cout << "Failed to load texture data" << std::endl;
	}

	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, tex_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(tex_data);
}

void loglr::texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, handle);
}
