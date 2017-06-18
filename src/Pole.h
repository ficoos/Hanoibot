#ifndef GC_POLE_H
#define GC_POLE_H

#include <memory>
#include <deque>

#include "Drawable.h"
#include "Movable.h"
#include "Ring.h"

using namespace std;

namespace gc {

class Pole final : public virtual Drawable, public virtual Movable {
public:
	Pole();
	void draw() const override;
	void position(Vector3D v) override;
	Vector3D position() const override;
	void height(float height);
	float height() const;
	void addRing(shared_ptr<Ring> ring);
	shared_ptr<Ring> popRing();
	shared_ptr<Ring> peekRing();
	int ringCount() const;
private:
	Vector3D _position;
	deque<shared_ptr<Ring>> _rings;
	float _height;
};
}

#endif // GC_POLE_H
