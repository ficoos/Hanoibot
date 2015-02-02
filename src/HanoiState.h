#include <memory>
#include <list>

#include <GLFW/glfw3.h>

#include "GameState.h"
#include "Ring.h"
#include "Pole.h"
#include "Matrix.h"
#include "Mouse.h"

using namespace std;

namespace gc {
class HanoiState final : public virtual GameState {
public:
	HanoiState(Mouse * mouse);
	void on_enter();
	virtual void update(double dt) override;
	virtual void draw() override;
	virtual void on_key_pressed(
		int key,
		int scancode,
		int action,
		int mods
	) override;
	virtual void on_resize(int width, int height) override;
	virtual bool should_close() override;
	virtual void on_mouse_move(double dx, double dy) override;
private:
	void draw_object(const Drawable & obj);
	bool _should_close;
	float _rotation_speed;
	float _current_rotation;
	Pole _pole_a;
	Pole _pole_b;
	Pole _pole_c;
	Vector3D _camera_pos;
	Matrix _camera_rot;
	Mouse * _mouse;
	list<shared_ptr<Ring>> _rings;

};
}
