#include "Ring.h"

#include <math.h>>

#include <GLFW/glfw3.h>

namespace gc {

Ring::Ring (float radius, Color color) {
	_radius = radius;
	_color = color;
}

Ring::~Ring() {}

void Ring::draw() {
	_color.set();
	int numc = 30;
	int numt = 30;
	float dist = _radius;
	float tube_rad = .2;

	int i, j, k;
	float s, t, x, y, z, twopi;

	twopi = 2 * M_PI;

	for (i = 0; i < numc; i++) {
		glBegin (GL_QUAD_STRIP);

		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (dist + tube_rad * cos (s * twopi / numc)) * cos (t * twopi / numt);
				y = (dist + tube_rad * cos (s * twopi / numc)) * sin (t * twopi / numt);
				z = tube_rad * sin (s * twopi / numc);

				glVertex3f (x, y, z);
			}
		}
		glEnd();
	}
}
}
