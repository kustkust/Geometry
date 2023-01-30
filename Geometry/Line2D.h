#pragma once
#include "Vector2D.h"
#include <iostream>
namespace gm {
	class Line2D {
	public:
		Vector2D n;//нормаль
		coord C;
		void calc(const Vector2D& t0, const Vector2D& t1);

		Line2D(const Vector2D& t0 = { 0.,0. }, const Vector2D& t1 = { 1.,1. });
		Line2D(const Vector2D& t0, const Vector2D& t1, int);
		Line2D(const Vector2D& n_, const coord& C_);
		Line2D(const coord x0, const  coord y0, const coord x1, const coord y1);
		Line2D(const Line2D& l);
		static const Line2D pointNormal(const Coord2D& p, const Vector2D& n_);

		void normalize();

		const Coord2D operator%(const Coord2D t) const;
		const coord operator|(const Coord2D& t) const;
		const coord operator/(const Coord2D& t) const;

		const gm::lenght operator/(const gm::Line2D& l) const;

		bool operator||(const Line2D& l) const;

		const Vector2D operator*(const Line2D l) const;

		const Line2D operator*(const coord l) const;
		Line2D& operator*=(const coord l);

		bool nei(const Vector2D& t, const coord& e) const;

		const coord ang_b(const Line2D& l)const;
		const coord operator^(const Line2D& l)const;

		const Coord2D projection(const Coord2D p)const;

		const Line2D relen_n(lenght k)const;
		Line2D& srelen_n(lenght k);

		friend std::ostream& operator<<(std::ostream& co, const Line2D& v);

		Vector2D getDir()const;
	};
}
