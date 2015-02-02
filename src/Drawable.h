#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace gc {
class Drawable {
public:
	virtual ~Drawable() {}
	virtual void draw() const = 0;
};
}

#endif // DRAWABLE_H
