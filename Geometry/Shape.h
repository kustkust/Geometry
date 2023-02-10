#pragma once
#include "ISizeable.h"
#include "Collision.h"

namespace gm {

	class IShape : public ISizeable {
	public:
		virtual bool inside(const Shape& other) const { throw "IShape"; };
		virtual bool inside(const IShape& other) const;
		virtual bool inside(const IShape* other) const;
		virtual bool inside(const Line& other) const = 0;
		virtual bool inside(const Sect& other) const = 0;
		virtual bool inside(const Circle& other) const = 0;
		virtual bool inside(const Rectangle& other) const = 0;

		virtual bool outside(const Shape& other) const { throw "IShape"; };
		virtual bool outside(const IShape& other) const;
		virtual bool outside(const IShape* other) const;
		virtual bool outside(const Line& other) const = 0;
		virtual bool outside(const Sect& other) const = 0;
		virtual bool outside(const Circle& other) const = 0;
		virtual bool outside(const Rectangle& other) const = 0;

		virtual Collision collides(const Shape& other) const { throw "IShape"; };
		virtual Collision collides(const IShape& other) const;
		virtual Collision collides(const IShape* other) const;
		virtual Collision collides(const Line& other) const = 0;
		virtual Collision collides(const Sect& other) const = 0;
		virtual Collision collides(const Circle& other) const = 0;
		virtual Collision collides(const Rectangle& other) const = 0;

		virtual bool fastCollides(const Shape& other) const { return !outside(other); };
		virtual bool fastCollides(const IShape& other) const;
		virtual bool fastCollides(const IShape* other) const;
		virtual bool fastCollides(const Line& other) const { return !outside(other); };
		virtual bool fastCollides(const Sect& other) const { return !outside(other); };
		virtual bool fastCollides(const Circle& other) const { return !outside(other); };
		virtual bool fastCollides(const Rectangle& other) const { return !outside(other); };

		virtual bool contains(const Coord& point) const = 0;

		template<class T>
		T* as() {
			return dynamic_cast<T*>(this);
		}
	};
	class Shape : public IShape {
		// using Sptr = std::unique_ptr<IShape>;
		using Sptr = IShape*;
		Sptr shape = nullptr;
	public:
		Shape() = default;
		Shape(Shape&&) noexcept;
		Shape(const Shape&) = delete;
		Shape& operator=(Shape&&) noexcept;
		Shape& operator=(const Shape&) = delete;

		Shape(IShape* sptr);

		virtual void scale(const Vector& scale) override;
		virtual const Vector getScale() const override;

		virtual void move(const Vector& v) override;
		virtual const Coord getPosition() const override;

		virtual const Size getSize() const override;
		virtual void setSize(const gm::Size& newSize) override;


		virtual bool inside(const Shape& other) const override;
		virtual bool inside(const Line& other) const override;
		virtual bool inside(const Sect& other) const override;
		virtual bool inside(const Circle& other) const override;
		virtual bool inside(const Rectangle& other) const override;

		virtual bool outside(const Shape& other) const override;
		virtual bool outside(const Line& other) const override;
		virtual bool outside(const Sect& other) const override;
		virtual bool outside(const Circle& other) const override;
		virtual bool outside(const Rectangle& other) const override;

		virtual Collision collides(const Shape& other) const override;
		virtual Collision collides(const Line& other) const override;
		virtual Collision collides(const Sect& other) const override;
		virtual Collision collides(const Circle& other) const override;
		virtual Collision collides(const Rectangle& other) const override;

		virtual bool contains(const Shape& other) const;
		virtual bool contains(const Coord& point) const override;

		IShape* get() {
			return shape;
		}

		const IShape* get() const {
			return shape;
		}

		~Shape() {
			if (shape != nullptr) {
				delete shape;
			}
		}
	};

	template<class T, class... Args>
	Shape makeShape(Args&&... args) {
		return Shape(new T(std::forward<Args>(args)...));
	}
}