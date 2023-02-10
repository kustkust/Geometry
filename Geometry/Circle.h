#pragma once
#include "Vector.h"
#include "Shape.h"
#include "Line.h"
#include "Sect.h"

namespace gm {
	class Circle : public IShape {
	public:
		Coord center;
		coord radius;
		const Vector getV()const;
		Circle(Coord c_, coord r_);
		Circle();
		void resize(const Coord& p);


		virtual void scale(const Vector& scale) override;
		virtual const Vector getScale() const override;
		virtual void move(const Vector& v) override;
		virtual const Coord getPosition() const override;
		virtual const Coord getCenter() const override;
		virtual void setCenter(const Coord& pos) override;

		virtual const Size getSize() const override;
		virtual void setSize(const gm::Size& newSize) override;

		virtual const Coord getLeftTop() const;
		virtual void setLeftTop(const Coord& lt);


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
