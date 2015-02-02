#include "Ring.h"

#include <math.h>

#include <GLFW/glfw3.h>

namespace gc {

Ring::Ring (float radius, Color color) {
	_torus = Torus(radius, .4);
	_color = color;
}

Vector3D Ring::position() const {
	return _position;

}

void Ring::position (Vector3D v) {
	_position = v;
}

Ring::~Ring() {}

void Ring::draw() const {
	glPushMatrix(); {
		_color.set();
		glRotatef(90, 1, 0, 0);
		_torus.draw();
	} glPopMatrix();
}
}
