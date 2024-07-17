#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace loglr{

class loglr_window {

public: // interface
	loglr_window(uint32_t w, uint32_t h, std::string name);
	~loglr_window();

	bool should_close() { return glfwWindowShouldClose(window); }
	GLFWwindow* handle() { return window; }

	loglr_window() = delete;
	loglr_window(const loglr_window&) = delete;
	loglr_window& operator=(const loglr_window&) = delete;

private: // members
	GLFWwindow* window;
	
	std::string window_name;
	const uint32_t width;
	const uint32_t height;

	bool init_window();
};
} // namespace loglr
#endif // WINDOW_H

