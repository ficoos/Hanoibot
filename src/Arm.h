#ifndef ARM_H
#define ARM_H

#include <memory>

using namespace std;

#include "Drawable.h"
#include "Movable.h"
#include "Ring.h"

namespace gc {
class Arm : public virtual Movable, public virtual Drawable {
public:
	Arm();
	void draw() const override;
	void position(Vector3D v) override;
	Vector3D position() const override;
	void update(double dt);
	void goal(Vector3D goal);
	Vector3D goal() const;
	shared_ptr<Ring> ring() const;
	bool hasReachedGoal() const;
	void setRing(shared_ptr<Ring> ring);
	void unsetRing();
private:
	Vector3D _position;
	float _armLength;
	float _forarmLength;
	float _handLength;
	Vector3D _shoulderRotXY;
	float _elbowRotX;
	Vector3D _goal;
	
	Vector3D _goal_shoulderRotXY;
	Vector3D _goal_wristRotXY;
	float _goal_elbowRotX;
	shared_ptr<Ring> _ring;
};
}

#endif // ARM_H
