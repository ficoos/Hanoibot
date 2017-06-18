#include "Torus.h"

#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace gc;

void Torus::draw() const {
	int numc = _circle_segments;
	int numt = _tube_segments;
	float dist = _radius;
	float tube_rad = _tube_radius;

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
