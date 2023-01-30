#include "IMoveable.h"
#include "Vector2D.h"

namespace gm {
	void IMoveable::move(const coord& x, const coord& y) {
		return move({ x,y });
	}

	void IMoveable::setPosition(const Vector2D& v) {
		return move(v - getPosition());
	}

	void IMoveable::setPosition(const coord& x, const coord& y) {
		return setPosition({ x,y });
	}
	IMoveable::~IMoveable() {
	}
}