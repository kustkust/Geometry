#include "IScaleable.h"
#include "Vector.h"

namespace gm {
	void IScaleable::scale(real _scale) {
		scale({ _scale, _scale });
	}

	void IScaleable::setScale(real _scale) {
		setScale({ _scale, _scale });
	}

	void IScaleable::setScale(const gm::Vector& scale_) {
		auto s = getScale();
		scale({ scale_.x / s.x,scale_.y / s.y });
	}

	gm::real gm::IScaleable::getXScale() const {
		return getScale().x;
	}

	gm::real gm::IScaleable::getYScale() const {
		return getScale().y;
	}

	IScaleable::~IScaleable() {
	}
}
