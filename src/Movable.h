#ifndef MOVABLE_H
#define MOVABLE_H

#include "Vector3D.h"

namespace gc {
class Movable {
public:
	virtual ~Movable() {}
	virtual void position(Vector3D v) = 0;
	virtual Vector3D position() const = 0;
};
}

#endif // MOVABLE_H
