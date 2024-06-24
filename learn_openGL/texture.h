#pragma once
#include <glad/glad.h>
#include <string>

namespace loglr {

class texture {

public:		// interface
	texture(const std::string& texture_path, GLuint pixel_format);

	GLuint id() { return handle; }

	void bind();

	texture() = delete;
	texture(const texture&) = delete;
	texture& operator=(const texture&) = delete;

private:	// members
	GLuint handle;

};
} // namespace loglr
