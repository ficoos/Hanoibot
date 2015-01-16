#include <memory>

#include "GameState.h"
#include "Ring.h"

using namespace std;

namespace gc {
class HanoiState final : public virtual GameState {
public:
	HanoiState();
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
private:
	bool _should_close;
	float _rotation_speed;
	float _current_rotation;
	unique_ptr<Ring> _ring;

};
}
