#include "Pole.h"

#include <GLFW/glfw3.h>

#include "Color.h"

using namespace gc;

void Pole::draw() const {
	Color(0.2, 0.2, 0.2).set();
	auto quad = gluNewQuadric();
	glRotatef(90, -1, 0, 0);
	gluCylinder(quad, 0.3, 0.3, this->height(), 5, 10);
	gluDeleteQuadric(quad);
	
	glRotatef(90, 1, 0, 0);
	for (auto ring : _rings) {
		glPushMatrix();
			ring->position().translate();
			ring->draw();
		glPopMatrix();
	}
}

Pole::Pole() {
}
void Pole::addRing (shared_ptr< Ring > ring) {
	_rings.push_front(ring);
	ring->position(Vector3D(0, (this->ringCount() - 1) * 0.85, 0));
}

shared_ptr< Ring > Pole::popRing() {
	auto res = _rings.front();
	_rings.pop_front();
	return res;
}

shared_ptr< Ring > Pole::peekRing() {
	if (_rings.size() == 0) {
		return shared_ptr<Ring>(nullptr);
	}
	return _rings.front();

}

int Pole::ringCount() const {
	return _rings.size();
}

Vector3D Pole::position() const {
	return _position;
}

void Pole::position(Vector3D v) {
	_position = v;
}

float Pole::height() const {
	return _height;
}

void Pole::height (float height) {
	_height = height;
}


