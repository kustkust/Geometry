#pragma once
#include <iostream>
#include "Vector.h"
#include "Shape.h"

namespace gm {
	class Line : IShape {
	public:
		Vector n;//нормаль
		coord C;
		void calc(const Vector& t0, const Vector& t1);

		Line(const Vector& t0 = { 0.,0. }, const Vector& t1 = { 1.,1. });
		Line(const Vector& n_, const coord& C_);
		Line(const coord x0, const  coord y0, const coord x1, const coord y1);
		Line(const Line& l);
		static const Line pointNormal(const Coord& p, const Vector& n_);

		void normalize();

		bool operator==(const Line& other) const;

		const Coord operator%(const Coord t) const;
		const coord operator/(const Coord& t) const;

		const lenght operator/(const gm::Line& l) const;

		bool operator||(const Line& l) const;

		const Coord operator*(const Line l) const;

		const Line operator*(const coord l) const;
		Line& operator*=(const coord l);

		const coord ang_b(const Line& l)const;
		const coord operator^(const Line& l)const;

		const Coord projection(const Coord p)const;

		const Line relen_n(lenght k)const;
		Line& srelen_n(lenght k);

		friend std::ostream& operator<<(std::ostream& out, const Line& v);

		Vector getDir()const;
		
		// Inherited via IShape
		virtual void scale(const Vector& scale) override;
		virtual const Vector getScale() const override;
		virtual void move(const Vector& v) override;
		virtual const Coord getPosition() const override;
		virtual const Size getSize() const override;
		virtual void setSize(const gm::Size& newSize) override;

		virtual bool inside(const Line& other) const override;
		virtual bool inside(const Sect& other) const override;
		virtual bool inside(const Circle& other) const override;
		virtual bool inside(const Rectangle& other) const override;

		virtual bool outside(const Line& other) const override;
		virtual bool outside(const Sect& other) const override;
		virtual bool outside(const Circle& other) const override;
		virtual bool outside(const Rectangle& other) const override;

		virtual Collision collides(const Line& other) const override;
		virtual Collision collides(const Sect& other) const override;
		virtual Collision collides(const Circle& other) const override;
		virtual Collision collides(const Rectangle& other) const override;

		virtual bool contains(const Coord& point) const override;
	};
}
