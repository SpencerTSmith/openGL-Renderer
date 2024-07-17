#include "loglr_window.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

loglr::loglr_window::loglr_window(uint32_t w, uint32_t h, std::string name) 
	: width{w}, height{h}, window_name{name} {
	init_window();
}

loglr::loglr_window::~loglr_window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool loglr::loglr_window::init_window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

