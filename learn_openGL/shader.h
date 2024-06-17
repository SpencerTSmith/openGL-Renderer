#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <glad/glad.h>

namespace loglr {

class shader {
public:
	shader(const char* vertex_path, const char* fragment_path);

	void use();
	shader() = delete;
	shader(const shader&) = delete;
	shader& operator=(const shader&) = delete;
	
private:
	GLuint handle;
};
}

#endif // !SHADER_H

