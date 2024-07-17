#include "shader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

loglr::shader::shader(const std::string& vertex_path, const std::string& fragment_path) {
	std::string vertex_source = read_source(vertex_path);
	std::string fragment_source = read_source(fragment_path);
	const GLchar* vert_cstr = vertex_source.c_str();
	const GLchar* frag_cstr = fragment_source.c_str();

	if (vertex_source.empty() || fragment_source.empty()) {
		std::cout << "ERROR::SHADER::FILE(S)_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vert_cstr, NULL);
	glCompileShader(vertex_shader);
	check_comp_link_errors(vertex_shader, CHECK_VERTEX);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_cstr, NULL);
	glCompileShader(fragment_shader);
	check_comp_link_errors(fragment_shader, CHECK_FRAGMENT);

	handle = glCreateProgram();
	glAttachShader(handle, vertex_shader);
	glAttachShader(handle, fragment_shader);
	glLinkProgram(handle);
	check_comp_link_errors(handle, CHECK_PROGRAM);
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
loglr::shader::~shader() {
	glDeleteProgram(handle);
}

void loglr::shader::use() {
	glUseProgram(handle);
}

std::string loglr::shader::read_source(const std::string& path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cout << "ERROR::SHADER::FILE(S)_NOT_OPENED" << std::endl;
	}

	std::string line;
	std::stringstream code_stream;
	while (std::getline(file, line)) {
		code_stream << line << '\n';
	}
	std::string source = code_stream.str();
	return source;
}

void loglr::shader::check_comp_link_errors(GLuint to_check, check_type type) {
	GLint success;
	char info_log[1024];

	if (type == CHECK_PROGRAM) {
		glGetProgramiv(to_check, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(to_check, 1024, NULL, info_log);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetShaderiv(to_check, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(to_check, 1024, NULL, info_log);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void loglr::shader::set_bool(const std::string& name, GLboolean value) const {
	glUniform1i(glGetUniformLocation(handle, name.c_str()), (GLint)value);
}
void loglr::shader::set_int(const std::string& name, GLint value) const {
	glUniform1i(glGetUniformLocation(handle, name.c_str()), value);
}
void loglr::shader::set_float(const std::string& name, GLfloat value) const {
	glUniform1f(glGetUniformLocation(handle, name.c_str()), value);
}

void loglr::shader::set_mat4(const std::string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
