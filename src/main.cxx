#include <memory>
#include <GLFW/glfw3.h>

#include "GameState.h"
#include "HanoiState.h"

using namespace std;
using namespace gc;

GameState* current_state = nullptr;

static void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mods
) {
	if (current_state) {
		current_state->on_key_pressed(key, scancode, action, mods);
	}
}

static void set_buffer_size_callback(
	GLFWwindow* window,
	int width,
	int height
) {
	if (current_state) {
		current_state->on_resize(width, height);
	}
}

static void update(double dt) {
	if (current_state) {
		current_state->update(dt);
	}
}

static void draw() {
	if (current_state) {
		current_state->draw();
	}
}

int main(int argc, char** argv) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	auto window = glfwCreateWindow(640, 480, "GC2", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, set_buffer_size_callback);

	glfwMakeContextCurrent(window);

	auto state = unique_ptr<HanoiState>(new HanoiState());
	current_state = state.get();

	{
		// Init projection
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		set_buffer_size_callback(window, width, height);
	}


	auto last_frame = glfwGetTime();
	double dt = 0;
	while (!glfwWindowShouldClose(window)) {
		dt = glfwGetTime() - last_frame;
		update(dt);
		if (current_state->should_close()) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		last_frame = glfwGetTime();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
