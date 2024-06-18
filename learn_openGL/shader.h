#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <glad/glad.h>

#include <string>

namespace loglr {

class shader {
public: // interface
	shader(const std::string& vertex_path, const std::string& fragment_path);
	~shader();

	void use();

	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	
	shader() = delete;
	shader(const shader&) = delete;
	shader& operator=(const shader&) = delete;
	
private: // members
	GLuint handle;

private: // implementation stuff
	enum check_type {
		CHECK_VERTEX,
		CHECK_FRAGMENT,
		CHECK_PROGRAM
	};

	std::string read_source(const std::string& path);
	void check_comp_link_errors(GLuint to_check, check_type type);

};
}

#endif // !SHADER_H

