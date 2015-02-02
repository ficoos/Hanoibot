#include "HanoiState.h"

#include <GLFW/glfw3.h>

using namespace gc;

static const double near = 1;
static const double far = 200;
static const int ring_count = 10;

HanoiState::HanoiState(Mouse * mouse) {
	_mouse = mouse;
	on_enter();
}

void HanoiState::on_enter() {
	glEnable (GL_NORMALIZE);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_COLOR_MATERIAL);
	glShadeModel (GL_SMOOTH);

	_should_close = false;
	_rotation_speed = 30;
	_current_rotation = 0;
	_camera_pos = {0, 0, -20};
	_pole_a.position ( {-5, 0, 0});
	_pole_b.position ( {0, 0, 0});
	_pole_c.position ( {5, 0, 0});
	
	_pole_a.height(ring_count * 50);
	_pole_b.height(ring_count * 50);
	_pole_c.height(ring_count * 50);
	
	for (int i = 0; i < ring_count; i++) {
		auto ring = shared_ptr<Ring>(new Ring((ring_count - i) * 0.2));
		_rings.push_front(ring);
		_pole_a.addRing(ring);
	}
};

void HanoiState::update (double dt) {
	_current_rotation += _rotation_speed * dt;
};

void HanoiState::on_mouse_move (double dx, double dy) {
	if (_mouse->get_button(0)) {
		_camera_rot.rotate(dx, 0, -1, 0);
		_camera_rot.rotate(dy, -1, 0, 0);
	} else if (_mouse->get_button(1)) {
		_camera_rot.rotate(dy, 0, 0, 1);
	}
}


void HanoiState::draw_object (const Drawable & obj) {
	glPushMatrix();
	auto movable = dynamic_cast<const Movable *> (&obj);
	if (movable) {
		movable->position().translate();
	}
	obj.draw();
	glPopMatrix();
}


void HanoiState::draw() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	_camera_pos.translate();
	_camera_rot.mult();
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv (GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv (GL_LIGHT0, GL_POSITION, lightPos0);

	draw_object(_pole_a);
	draw_object(_pole_b);
	draw_object(_pole_c);
	for (auto ring : _rings) {
		draw_object(*ring);
	}
	glPopMatrix();
};
void HanoiState::on_key_pressed (
        int key,
        int scancode,
        int action,
        int mods
) {
	if (action == GLFW_PRESS) {
		switch(key) {
		case GLFW_KEY_ESCAPE:
			_should_close = true;
			break;
		case GLFW_KEY_R:
			_camera_rot = Matrix();
			_camera_pos = {0, 0, -20};
			break;
		}
	}
};

bool HanoiState::should_close() {
	return _should_close;
}

void HanoiState::on_resize (int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (
	        45.0,
	        (double) width / (double) height,
	        near,
	        far
	);
};
