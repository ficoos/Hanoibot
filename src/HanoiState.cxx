#include "HanoiState.h"

#include <GLFW/glfw3.h>

namespace gc {

static const double near = 1;
static const double far = 200;

	HanoiState::HanoiState() {
		on_enter();
	}
	void HanoiState::on_enter() {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);

		_should_close = false;
		_rotation_speed = 30;
		_current_rotation = 0;
		_ring = unique_ptr<Ring>(new Ring(1, {1, 0, 0}));
	};
	void HanoiState::update(double dt) {
		_current_rotation += _rotation_speed * dt;
	};
	void HanoiState::draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0, 0, -20);
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	    	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

		glRotatef(_current_rotation, 0.f, 1.f, 0.f);
		glColor3f(255, 0, 0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);

			//Front
			glNormal3f(0.0f, 0.0f, 1.0f);
			//glNormal3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(-1.5f, -1.0f, 1.5f);
			//glNormal3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.5f, -1.0f, 1.5f);
			//glNormal3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.5f, 1.0f, 1.5f);
			//glNormal3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(-1.5f, 1.0f, 1.5f);

			//Right
			glNormal3f(1.0f, 0.0f, 0.0f);
			//glNormal3f(1.0f, 0.0f, -1.0f);
			glVertex3f(1.5f, -1.0f, -1.5f);
			//glNormal3f(1.0f, 0.0f, -1.0f);
			glVertex3f(1.5f, 1.0f, -1.5f);
			//glNormal3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.5f, 1.0f, 1.5f);
			//glNormal3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.5f, -1.0f, 1.5f);

			//Back
			glNormal3f(0.0f, 0.0f, -1.0f);
			//glNormal3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.5f, -1.0f, -1.5f);
			//glNormal3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.5f, 1.0f, -1.5f);
			//glNormal3f(1.0f, 0.0f, -1.0f);
			glVertex3f(1.5f, 1.0f, -1.5f);
			//glNormal3f(1.0f, 0.0f, -1.0f);
			glVertex3f(1.5f, -1.0f, -1.5f);

			//Left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			//glNormal3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.5f, -1.0f, -1.5f);
			//glNormal3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(-1.5f, -1.0f, 1.5f);
			//glNormal3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(-1.5f, 1.0f, 1.5f);
			//glNormal3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.5f, 1.0f, -1.5f);

		glEnd();
		glTranslatef(10, 0, 0);
		_ring->draw();
		};
	void HanoiState::on_key_pressed(
		int key,
		int scancode,
		int action,
		int mods
	) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			_should_close = true;
		}
	};

	bool HanoiState::should_close() {
		return _should_close;
	}

	void HanoiState::on_resize(int width, int height) {
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(
			45.0,
			(double)width / (double)height,
			near,
			far
		);
	};
}
