#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GLFW/glfw3.h>

namespace gc {
class Vector3D final {
public:
	Vector3D (float x = 0, float y = 0, float z = 0) : x {x}, y {y}, z {z} {}
	~Vector3D() {}
	inline Vector3D operator+ (const Vector3D & rhs) {
		auto lhs = *this;
		return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}
	
	inline Vector3D operator+= (const Vector3D & rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	
	inline Vector3D operator-= (const Vector3D & rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	
	inline bool operator== (const Vector3D & rhs) const {
		auto lhs = *this;
		return (
			lhs.x == rhs.x
			&& lhs.y == rhs.y
			&& lhs.z == rhs.z
		);
	}
	inline Vector3D operator* (const float & rhs) {
		auto lhs = *this;
		return Vector3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}
	
	inline Vector3D operator- (const Vector3D & rhs) {
		auto lhs = *this;
		return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	void translate() const {
		glTranslatef (x, y, z);
	}
	void rotate() const {
		glRotatef (x, 1, 0, 0);
		glRotatef (y, 0, 1, 0);
		glRotatef (z, 0, 0, 0);
	}

	float x;
	float y;
	float z;

};
}
#endif
