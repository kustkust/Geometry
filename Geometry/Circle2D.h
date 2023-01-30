#pragma once
#include "Vector2D.h"
#include "Line2D.h"
#define ac 32
namespace gm {
	class Circle2D {
	public:
		Coord2D c;
		coord r;
		const Vector2D getV() const;
		Circle2D(Coord2D c_, coord r_);
		Circle2D();
		const short int ins(const Line2D& l, Coord2D& ans1, Coord2D& ans2) const;
		const bool isins(const Line2D& l) const;
		const int ins(const Circle2D& other, Coord2D& ans1, Coord2D& ans2) const;
		void resize(const Coord2D& p);
	};
}
