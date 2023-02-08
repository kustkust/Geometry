#pragma once
#include "Vector.h"
#include "Shape.h"

namespace gm {
	class Sect : public IShape {
	public:
		Coord p0, p1;
		Sect();
		Sect(const Coord&p0_, const Coord&p1_);
		Sect(coord x0, coord y0, coord x1, coord y1);

		const Line getLine() const;

		bool intersection(const Sect&s, gm::Coord&p)const;

		static std::vector<Sect> getSects(const std::vector<Coord>&points);
		const bool between(const Coord p)const;
		gm::lenght deviation(const gm::Coord&p)const;
		gm::lenght lenght(const gm::Coord&p)const;

		// Inherited via IShape
		virtual void scale(const Vector& scale) override;
		virtual const Vector getScale() const override;
		
		virtual void move(const Vector& v) override;
		virtual const Coord getPosition() const override;
		virtual const Coord getCenter() const override;
		virtual const Coord getLeftTop() const override;
		virtual const Coord getRightBottom() const override;
		
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