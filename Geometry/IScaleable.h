#pragma once
#include "Geometry.def.h"

namespace gm {
	class IScaleable {
	public:
		virtual void scale(const Vector& scale) abstract;
		virtual void scale(real scale);
		virtual void setScale(const Vector& scale);
		virtual void setScale(real scale);
		virtual const Vector getScale()const abstract;
		virtual real getXScale()const;
		virtual real getYScale()const;
		virtual ~IScaleable();
	};
}