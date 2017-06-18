#ifndef GC_TORUS_H
#define GC_TORUS_H

#include "Drawable.h"

namespace gc {

class Torus final : public virtual Drawable {
public:
	Torus(
		float radius = 1,
		float tube_radius = .1,
		unsigned int tube_sgements = 30,
		unsigned int circle_segments = 30
	) :
	_radius{radius},
	_tube_radius{tube_radius},
	_tube_segments{tube_sgements},
	_circle_segments{circle_segments} {}

	void draw() const override;
private:
	float _radius;
	float _tube_radius;
	unsigned int _tube_segments;
	unsigned int _circle_segments;
};
}

#endif // GC_TORUS_H
