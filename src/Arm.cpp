#include "Arm.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <GLFW/glfw3.h>

#include "Color.h"

using namespace gc;

Arm::Arm() {
	_armLength = 8;
	_forarmLength = 8;
	_handLength = 1;
	_shoulderRotXY.x = 0;
	_elbowRotX = 0;
	_goal_shoulderRotXY = _shoulderRotXY;
	_goal_elbowRotX = _elbowRotX;
	unsetRing();
}

static float myabs(float v) {
	return v < 0 ? -v : v;
}

static void rotate_towards(float &ang, float dst, float speed) {
	if (myabs(ang - dst) < speed) {
		ang = dst;
		return;
	};
	if (ang < dst) {
		ang += speed;
	} else {
		ang -= speed;
	}
}

void Arm::update (double dt) {
	rotate_towards(_shoulderRotXY.x, _goal_shoulderRotXY.x, 100 * dt);
	rotate_towards(_shoulderRotXY.y, _goal_shoulderRotXY.y, 100 * dt);
	rotate_towards(_elbowRotX, _goal_elbowRotX, 100 * dt);
}


void Arm::draw() const {
	Color(0.8, 0.8, 0.8).set();
	auto quad = gluNewQuadric();
	glRotatef(_shoulderRotXY.x, 1, 0, 0);
	glRotatef(_shoulderRotXY.y, 0, 1, 1);
	gluCylinder(quad, 0.3, 0.3, _armLength, 5, 10);
	glTranslatef(0, 0, _armLength);
	
	glRotatef(180 - _elbowRotX, 1, 0, 0);
	Color(0.8, 0.8, 0.1).set();
	gluCylinder(quad, 0.3, 0.3, _forarmLength, 5, 10);
	glTranslatef(0, 0, _armLength);
	
	glRotatef(_elbowRotX - _shoulderRotXY.x - 180, 1, 0, 0);
	glRotatef(_shoulderRotXY.y, 0, -1, 0);
	Color(0.8, 0.1, 0.1).set();
	gluCylinder(quad, 0.3, 0.3, _handLength, 5, 10);
	gluDeleteQuadric(quad);
	glTranslatef(0, 0, _handLength);
	if (_ring != nullptr) {
		_ring->position().translate();
		_ring->draw();
	}

}
Vector3D Arm::position() const {
	return _position;
}

void Arm::position (Vector3D v) {
	_position = v;
}
shared_ptr< Ring > Arm::ring() const {
	return _ring;
}
static double getAngle(double a, double b, double c) {
	auto top = (a * a) + (b * b) - (c * c);
	auto bottom = 2 * a * b;
	auto final = top/bottom;
	if (final > 1) {
		return acos(1);
	} else if (final < -1) {
		return acos(-1);
	}
	return acos(final);
}

void Arm::setRing (shared_ptr< Ring > ring) {
	ring->position({0.f, 0.f, ring->radius() + 0.4f});
	_ring = ring;
}

void Arm::unsetRing () {
	_ring = shared_ptr<Ring>(nullptr);
}

bool Arm::hasReachedGoal() const {
	return (
		_elbowRotX == _goal_elbowRotX
		&& _shoulderRotXY == _goal_shoulderRotXY
	);
}

Vector3D Arm::goal() const {
	return _goal;
}

void Arm::goal (Vector3D goal) {
	_goal = goal;
	
	auto norm_dst = _goal - _position - Vector3D(0, -.2f, _handLength);
	auto b = sqrt(norm_dst.z * norm_dst.z + norm_dst.y * norm_dst.y + norm_dst.x * norm_dst.x);
	auto l1 = _armLength;
	auto l2 = _forarmLength;
	auto q1 = atan2(norm_dst.y, norm_dst.z);
	auto q2 = getAngle(l1, b, l2);
	_goal_shoulderRotXY.x = -(q1 + q2) * (180 / M_PI);
	_goal_shoulderRotXY.y = (atan2(norm_dst.x, norm_dst.z)) * (180 / M_PI);
	_goal_elbowRotX = getAngle(l1, l2, b) * (180 / M_PI);
}
