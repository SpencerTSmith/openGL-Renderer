#include "app.h"

#include <iostream>

#include "shader.h"

const char* vertex_shader_source =
"#version 460 core\n"
"layout (location = 0) in vec3 a_pos;\n"
"layout (location = 1) in vec3 a_color;\n"
"out vec3 vertex_color;\n"
"void main() {\n"
"gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
"vertex_color = a_color;\n"
"}\0";

const char* fragment_shader_source =
"#version 460 core\n"
"out vec4 frag_color;\n"
"in vec3 vertex_color;\n"
"void main() {\n"
"frag_color = vec4(vertex_color, 1.0);\n"
"}\n";

float vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

loglr::app::app(std::string name)
	: name{ name }, window{ width, height, name } {

}

void loglr::app::run() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return;
	}
	
	// custom mode
	loglr::shader shader("shaders/first.vert", "shaders/first.frag");

	// Generate a vertex array, stores all attribute stuff and the vertex buffer
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Generate a vertex buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);

	/*GLuint EBO;
	glGenBuffers(1, &EBO);*/

	// Bind the vertex array to save all subsequent vertex information, including the EBO
	glBindVertexArray(VAO);

	// Bind the gl vertex buffer to vbo, and give it the data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO to the element array, and give it the index data
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
	
	// This configures the currently bound vbo to GL_ARRAY_BUFFER, specifies what attributes are in the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);						// location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));		// color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	while (!window.should_close()) {
		glfwPollEvents();
		process_input();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader
		shader.use();

		// Use the vertex array
		glBindVertexArray(VAO);
		// Draw array using triangle primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw elements using vao and ebo
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window.handle());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	/*glDeleteBuffers(1, &EBO);*/
	glDeleteBuffers(1, &VBO);
}

void loglr::app::process_input()
{
	if (glfwGetKey(window.handle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.handle(), true);
}
