#ifndef __GC_GAMESTATE_H__
#define __GC_GAMESTATE_H__
namespace gc {
class GameState {
public:
	virtual void update(double dt) = 0;
	virtual void draw() = 0;
	virtual void on_key_pressed(
		int key,
		int scancode,
		int action,
		int mods
	) = 0;
	virtual void on_resize(int width, int height) = 0;
	virtual bool should_close() = 0;
};
}
#endif
