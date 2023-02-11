#pragma once
#include <bitset>
#include "Vector.h"
#include "Shape.h"
#include "SFML/Graphics/Rect.hpp"

namespace gm {
	class Rectangle : public IShape {
		Coord leftTop;
		Size size;
	public:
		Rectangle();
		Rectangle(const Coord& leftTop, const Size& size);
		Rectangle(coord left, coord top, real width, real heigth);
		static Rectangle LTRB(const Coord& leftTop, const Coord& rightBottom);

		bool operator==(const Rectangle& other)const;
		bool operator!=(const Rectangle& other)const;

		void move(const Vector& v) override;
		const Coord getPosition()const override;

		const Size getSize() const override;
		void setSize(const gm::Size& newSize) override;

		const Vector getScale()const override;
		void scale(const gm::Vector& scale) override;

		bool contains(const Coord& point) const override;

		const Rectangle getBounds() const override;

		const Sect getLeftSect() const;
		const Sect getTopSect() const;
		const Sect getRightSect() const;
		const Sect getBottomSect() const;

		
		using IShape::inside;
		virtual bool inside(const Line& other) const override;
		virtual bool inside(const Sect& other) const override;
		virtual bool inside(const Circle& other) const override;
		virtual bool inside(const Rectangle& other) const override;

		using IShape::outside;
		virtual bool outside(const Line& other) const override;
		virtual bool outside(const Sect& other) const override;
		virtual bool outside(const Circle& other) const override;
		virtual bool outside(const Rectangle& other) const override;

		using IShape::collides;
		virtual Collision collides(const Line& other) const override;
		virtual Collision collides(const Sect& other) const override;
		virtual Collision collides(const Circle& other) const override;
		virtual Collision collides(const Rectangle& other) const override;

#ifdef SFML_RECT_HPP
		template<class T>
		Rectangle(const sf::Rect<T>& rect) : leftTop(rect.left, rect.top), size(rect.width, rect.height) {

		}
		template<class T>
		Rectangle& operator =(const sf::Rect<T>& rect) {
			leftTop.x = rect.left;
			leftTop.y = rect.top;
			size.x = rect.width;
			size.y = rect.height;
		}
#endif
	};

	class RectangleColl : public ICollison {
		Rectangle coll;
		std::bitset<4> corners;
		bool collide;
	public:
		RectangleColl(bool coll);
		RectangleColl(const Rectangle& rect, int first, int second);
		RectangleColl(const Rectangle& rect, std::bitset<4> corners);
		operator bool() const override;
		PointsArray getPoints() const override;
		const Rectangle& getRect() const;
		const Coord getFirst() const;
		const Coord getSecond() const;
		bool islt() const;
		bool isrt() const;
		bool islb() const;
		bool isrb() const;
	};
}
