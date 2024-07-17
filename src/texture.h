#ifndef TEXTURE_H
#define TEXTURE_
#pragma once

#include <glad/glad.h>

#include <string>

namespace loglr {

class texture {

public:		// interface
	texture(const std::string& texture_path, GLuint pixel_format);

	GLuint id() const { return handle; }

	void bind() const;

	texture() = delete;
	texture(const texture&) = delete;
	texture& operator=(const texture&) = delete;

private:	// members
	GLuint handle;

};
} // namespace loglr
#endif // !TEXTURE_H
