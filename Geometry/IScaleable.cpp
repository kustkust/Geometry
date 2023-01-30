#include "IScaleable.h"
#include "Vector2D.h"

namespace gm {
	void IScaleable::scale(real _scale) {
		scale({ _scale, _scale });
	}

	void IScaleable::setScale(real _scale) {
		setScale({ _scale, _scale });
	}

	const Vector2D IScaleable::getScale() const {
		return { getXScale(), getYScale() };
	}

	void IScaleable::setScale(const gm::Vector2D& scale_) {
		auto s = getScale();
		scale({ scale_.x / s.x,scale_.y / s.y });
	}

	IScaleable::~IScaleable() {
	}
}
