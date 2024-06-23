#include "app.h"

#include <iostream>

#include "shader.h"
#include "utilities/stb_image.h"

GLfloat vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

GLfloat tex_coords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f
};

GLfloat rect_verts[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

GLuint rect_indices[] = {
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
	
	loglr::shader shader("shaders/first.vert", "shaders/first.frag");

	stbi_set_flip_vertically_on_load(true);
	int32_t width, height, num_channels;
	GLubyte* tex_data = stbi_load("resources/container.jpg", &width, &height, &num_channels, 0);
	if (!tex_data) {
		std::cout << "Failed to load texture data" << std::endl;
	}
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(tex_data);

	GLubyte* happy_data = stbi_load("resources/awesomeface.png", &width, &height, &num_channels, 0);
	if (!happy_data) {
		std::cout << "Failed to load texture data" << std::endl;
	}
	GLuint happy;
	glGenTextures(1, &happy);
	glBindTexture(GL_TEXTURE_2D, happy);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, happy_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(happy_data);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Generate a vertex array, stores all attribute stuff and the vertex buffer
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Generate a vertex buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	// Bind the vertex array to save all subsequent vertex information, including the EBO
	glBindVertexArray(VAO);

	// Bind the gl vertex buffer to vbo, and give it the data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_verts), rect_verts, GL_STATIC_DRAW);

	// Bind EBO to the element array, and give it the index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);
	
	// This configures the currently bound vbo to GL_ARRAY_BUFFER, specifies what attributes are in the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);						// location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));		// color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));		// tex_coords
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Use the shader
	shader.use();
	shader.set_int("texture1", 0);
	shader.set_int("texture2", 1);

	while (!window.should_close()) {
		glfwPollEvents();
		process_input();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, happy);

		// Use the vertex array
		glBindVertexArray(VAO);
		// Draw array using triangle primitive
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/

		// Draw elements using vao and ebo
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
