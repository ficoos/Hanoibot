#ifndef __GC_MATRIX_H__
#define __GC_MATRIX_H__

#include <math.h>
#include <tuple>

#include <GLFW/glfw3.h>

using namespace std;

namespace gc {
class Matrix final {
public:
	Matrix() {
		glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, _mat);
		glPopMatrix();
		
	};
	float operator[](tuple<int, int> idx) {
		return _mat[get<1>(idx) * 4 + get<0>(idx)];
	}
	
	void rotate(float phi, float x, float y, float z) {
		glPushMatrix();
		glLoadIdentity();
		glRotatef(phi, x, y, z);
		glMultMatrixf(_mat);
		glGetFloatv(GL_MODELVIEW_MATRIX, _mat);
		glPopMatrix();
	}

	void mult() const { glMultMatrixf(_mat); };
private:
	GLfloat _mat[16];
};
}
#endif