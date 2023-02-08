#include "IMoveable.h"
#include "Vector.h"

namespace gm {
	void IMoveable::move(const coord& x, const coord& y) {
		return move({ x,y });
	}

	void IMoveable::setPosition(const Coord& v) {
		return move(v - getPosition());
	}

	void IMoveable::setPosition(const coord& x, const coord& y) {
		return setPosition({ x,y });
	}
	const real IMoveable::getX() const {
		return getPosition().x;
	}
	const real IMoveable::getY() const {
		return getPosition().y;
	}
	IMoveable::~IMoveable() {
	}
}