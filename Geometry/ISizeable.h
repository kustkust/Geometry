#pragma once
#include "IScaleable.h"
#include "IMoveable.h"

namespace gm {
	class Rectangle;
	class ISizeable : public IScaleable, public IMoveable {
	public:
		virtual const Size getSize() const abstract;
		virtual void setSize(const gm::Size& newSize) abstract;
		virtual void setSize(gm::lenght newSize);
		virtual lenght getWidth() const;
		virtual lenght getHeight() const;

		virtual const Coord getCenter() const;
		virtual void setCenter(const Coord& center);

		virtual const Coord getLeftTop() const;
		virtual const Coord getRightTop() const;
		virtual const Coord getLeftBottom() const;
		virtual const Coord getRightBottom() const;

		virtual void setLeftTop(const Coord& lt);
		virtual void setRightTop(const Coord& rt);
		virtual void setLeftBottom(const Coord& lb);
		virtual void setRightBottom(const Coord& rb);

		virtual coord getLeft() const;
		virtual coord getRight() const;
		virtual coord getTop() const;
		virtual coord getBottom() const;

		virtual const Coord getLeftCenter() const;
		virtual const Coord getRightCenter() const;
		virtual const Coord getTopCenter() const;
		virtual const Coord getBottomCenter() const;

		virtual const Rectangle getBounds() const;

		virtual ~ISizeable() = default;
	};
}