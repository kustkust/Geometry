#pragma once
#include "Geometry.def.h"

namespace gm {
	class IMoveable {
	public:
		virtual void move(const Vector& v)abstract;
		virtual void move(const coord& x, const coord& y);
		virtual void setPosition(const Coord& v);
		virtual void setPosition(const coord& x, const coord& y);
		virtual const Coord getPosition()const abstract;
		virtual const real getX()const;
		virtual const real getY()const;
		virtual ~IMoveable();
	};
}