#include "HanoiState.h"

#include <GLFW/glfw3.h>

using namespace gc;

static const double near = 1;
static const double far = 200;
static const int ring_count = 10;
static const Color ring_colors[] {
	Color(1, 0, 0),
	Color(0, 1, 0),
	Color(0, 0, 1),
	Color(0, 1, 1),
	Color(1, 1, 0),
	Color(1, 0, 1),
	Color(1, .5, 1),
	Color(1, .5, .5),
	Color(.5, .5, 0),
	Color(.5, .5, 1)
};

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
	_camera_pos = {0, 0, -20};
	_pole_a.position ( {-5, -5, 0});
	_pole_b.position ( {0, -5, 0});
	_pole_c.position ( {5, -5, 0});
	goal = nullptr;
	
	_pole_a.height(ring_count * 0.9);
	_pole_b.height(ring_count * 0.9);
	_pole_c.height(ring_count * 0.9);
	
	_arm.position({0, 0, -10});
	_arm.goal({0, -5, 0});
	
	for (int i = 0; i < ring_count; i++) {
		auto ring = shared_ptr<Ring>(new Ring((ring_count - i) * 0.2 + 0.5, ring_colors[i]));
		_rings.push_front(ring);
		_pole_a.addRing(ring);
	}
};

void HanoiState::update (double dt) {
	_arm.update(dt);
	if (_arm.hasReachedGoal()) {
		if (goal) {
			if (!isAbovePole) {
				Vector3D target = goal->position();
				auto topRing = goal->peekRing();
				if (topRing != nullptr) {
					target += topRing->position() + Vector3D(0, 0.425, 0);
				}
				if (_arm.ring() != nullptr) {
					target -= Vector3D(0, 0, _arm.ring()->radius() + .4f);
				} else if (topRing != nullptr) {
					target -= Vector3D(0, 0, topRing->radius() + .4f);
				} else {
					_arm.goal({0, 0, -5});
					goal = nullptr;
					return;
				}
				isAbovePole = true;
				_arm.goal(target);
			} else {
				if (_arm.ring() != nullptr) {
					goal->addRing(_arm.ring());
					_arm.unsetRing();
				} else if (goal->peekRing() != nullptr) {
					_arm.setRing(goal->popRing());
				}
				_arm.goal(goal->position() + Vector3D(0, goal->height() + 1, -.4f));
				isAbovePole = false;
				goal = nullptr;
			}
		} else {
			if (!isAbovePole) {
				_arm.goal({0, 0, -5});
				isAbovePole = true;
			}
		}
	}
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
	GLfloat ambientColor[] = {0.02f, 0.02f, 0.02f, 1.0f};
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = {2.0f, -5.0f, 3.0f, 1.0f};
	glLightfv (GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv (GL_LIGHT0, GL_POSITION, lightPos0);

	draw_object(_pole_a);
	draw_object(_pole_b);
	draw_object(_pole_c);
	draw_object(_arm);
	glPopMatrix();
};

void HanoiState::goToPole(Pole & pole) {
	auto topRing = pole.peekRing();
	Vector3D target = pole.position() + Vector3D(0, pole.height() + 1, -4.f);
	if (_arm.ring() != nullptr) {
		target -= Vector3D(0, 0, _arm.ring()->radius() + .4f);
	} else if (topRing != nullptr) {
		target -= Vector3D(0, 0, topRing->radius() + .4f);
	}
	isAbovePole = false;
	_arm.goal(target);
	goal = &pole;
}

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
		case GLFW_KEY_Q:
			goToPole(_pole_a);
			break;
		case GLFW_KEY_W:
			goToPole(_pole_b);
			break;
		case GLFW_KEY_E:
			goToPole(_pole_c);
			break;
		case GLFW_KEY_UP:
			_arm.goal(_arm.goal() + Vector3D(0, 1, 0));
			break;
		case GLFW_KEY_LEFT:
			_arm.goal(_arm.goal() + Vector3D(0, 0, 1));
			break;
		case GLFW_KEY_RIGHT:
			_arm.goal(_arm.goal() + Vector3D(0, 0, -1));
			break;
		case GLFW_KEY_DOWN:
			_arm.goal(_arm.goal() + Vector3D(0, -1, 0));
			break;
		case GLFW_KEY_A:
			_arm.goal(_arm.goal() + Vector3D(-1, 0, 0));
			break;
		case GLFW_KEY_Z:
			_arm.goal(_arm.goal() + Vector3D(1, 0, 0));
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
