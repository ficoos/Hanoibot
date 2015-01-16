#ifndef __GC_RING_H__
#define __GC_RING_H__

#include "Color.h"
#include "Drawable.h"

namespace gc {
class Ring : public virtual Drawable {
public:
	Ring(float radius, Color color={1, 1, 1});
	virtual ~Ring();

	void draw();
private:
	float _radius;
	Color _color;
};
}
#endif
