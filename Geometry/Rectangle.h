#pragma once
#include "Vector2D.h"
#include "IMoveable.h"
#include "ISizeable.h"
#include <optional>
#include "SFML/Graphics/Rect.hpp"

namespace gm {
	class Rectangle : public IMoveable, public ISizeable {
		Coord2D leftTop;
		Size2D size;
	public:
		Rectangle();
		Rectangle(const Coord2D& leftTop, const Size2D& size);
		Rectangle(coord left, coord top, real width, real heigth);
		static Rectangle LTRB(const Coord2D& leftTop, const Coord2D& rightBottom);

		bool operator==(const Rectangle& other)const;
		bool operator!=(const Rectangle& other)const;

		void move(const Vector2D& v) override;
		const Coord2D getPosition()const override;
		Coord2D getCenter()const;
		void setCenter(const Coord2D& center);

		void scale(const Vector2D& scale);
		real getXScale()const override;
		real getYScale()const override;

		const Size2D getSize() const override;
		void setSize(const gm::Size2D& newSize) override;

		const Coord2D getLeftTop() const;
		const Coord2D getRightTop() const;
		const Coord2D getLeftBottom() const;
		const Coord2D getRightBottom() const;

		coord getLeft()const;
		coord getRight()const;
		coord getTop()const;
		coord getBottom()const;

		std::optional<Rectangle> intersect(const Rectangle& other) const;
		bool inside(const Rectangle& other) const;
		bool contain(const Rectangle& other) const;

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
}
