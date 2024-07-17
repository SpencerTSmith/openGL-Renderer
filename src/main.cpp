#include "app.h"
 
int main() {
	loglr::app renderer{ "lOGLr" };

	renderer.run();
}


//int main() {
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	loglr::app renderer{ "loGLR" };
//	renderer.run();
//
//	
//
//	while (!glfwWindowShouldClose(window)) {
//		process_input(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// render stuff here
//
//		// Use the shader
//		glUseProgram(shader_program);
//		// Use the vertex array
//		glBindVertexArray(VAO);
//		// Draw array using triangle primitive
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		// Draw elements using vao and ebo
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &EBO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shader_program);
//
//
//	glfwTerminate();
//	return 0;
//}


