#pragma once
#include "Geometry.def.h"

namespace gm {
	class IScaleable {
	public:
		virtual void scale(const Vector2D& scale) abstract;
		virtual void scale(real scale);
		virtual void setScale(const Vector2D& scale);
		virtual void setScale(real scale);
		virtual const Vector2D getScale()const;
		virtual real getXScale()const abstract;
		virtual real getYScale()const abstract;
		virtual ~IScaleable();
	};
}