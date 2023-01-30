#pragma once
#include "IScaleable.h"

namespace gm {
	class ISizeable: public IScaleable {
		virtual const Size2D getSize() const abstract;
		virtual void setSize(const gm::Size2D& newSize) abstract;
	};
}