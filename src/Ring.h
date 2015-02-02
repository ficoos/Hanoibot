#ifndef __GC_RING_H__
#define __GC_RING_H__

#include "Color.h"
#include "Movable.h"
#include "Torus.h"
#include "Drawable.h"

namespace gc {
class Ring final : public virtual Drawable, public virtual Movable {
public:
	Ring(float radius, Color color={1, 1, 1});
	virtual ~Ring();
	void position(Vector3D v) override;
	Vector3D position() const override;

	void draw() const override;
private:
	float _radius;
	Color _color;
	Torus _torus;
	Vector3D _position;
};
}
#endif
