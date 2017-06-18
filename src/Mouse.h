#ifndef __GC_MOUSE_H__
#define __GC_MOUSE_H__

#include <GLFW/glfw3.h>

namespace gc {
class Mouse final {
public:
	Mouse(GLFWwindow * wnd) {
		_wnd = wnd;
	}
	
	Mouse(const Mouse & obj);
	Mouse& operator=( const Mouse & );
	
	int get_button(int button) const {
		return glfwGetMouseButton(_wnd, button);
	}
private:
	GLFWwindow * _wnd;
};
}

#endif