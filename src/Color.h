#ifndef __GC_COLOR_H__
#define __GC_COLOR_H__

#include <GLFW/glfw3.h>

namespace gc {
class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color() : r{0}, g{0}, b{0}, a{0} {}
	Color(float r, float g, float b) : r{r}, g{g}, b{b}, a{1} {}
	Color(float r, float g, float b, float a) : r{r}, g{g}, b{b}, a{a} {}

	void set() { glColor4f(r, g, b, a); };
};
}
#endif
