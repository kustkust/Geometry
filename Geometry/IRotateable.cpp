#include "IRotateable.h"

namespace gm {
	void IRotateable::setRotation(const gm::angle& ang) {
		rotate(ang - getRotation());
	}
	IRotateable::~IRotateable() {
	}
}
