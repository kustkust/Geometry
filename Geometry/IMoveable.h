#pragma once
#include "Geometry.def.h"

namespace gm {
	class IMoveable {
	public:
		virtual void move(const Vector2D& v)abstract;
		virtual void move(const coord& x, const coord& y);
		virtual void setPosition(const Vector2D& v);
		virtual void setPosition(const coord& x, const coord& y);
		virtual const Coord2D getPosition()const abstract;
		virtual ~IMoveable();
	};
}