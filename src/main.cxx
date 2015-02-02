#include <memory>
#include <GLFW/glfw3.h>

#include "GameState.h"
#include "HanoiState.h"
#include "Mouse.h"

using namespace std;
using namespace gc;

double last_cur_x = 0;
double last_cur_y = 0;

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

	auto mouse = unique_ptr<Mouse>(new Mouse(window));
	auto state = unique_ptr<HanoiState>(new HanoiState(mouse.get()));
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
		double mx, my;
		dt = glfwGetTime() - last_frame;
		update(dt);
		if (current_state->should_close()) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		last_frame = glfwGetTime();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwGetCursorPos(window, &mx, &my);
		if (mx != last_cur_x || my != last_cur_y) {
			current_state->on_mouse_move(
				last_cur_x - mx,
				last_cur_y - my
			);
			last_cur_x = mx;
			last_cur_y = my;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
