#pragma once
#include "Geometry.def.h"
#include "IRotateable.h"
#include "IScaleable.h"

namespace gm {
	class Matrix2: public IRotateable, public IScaleable {
	public:
		real m[4];

		Matrix2();
		Matrix2(const Matrix2& _m);
		Matrix2(Matrix2&& _m) noexcept;
		Matrix2(angle a);
		Matrix2(real m11, real m12, real m21, real m22);
		Matrix2(real _m[4]);

		Matrix2& operator=(const Matrix2& _m);
		Matrix2& operator=(Matrix2&& _m) noexcept;

		bool operator==(const Matrix2& m);
		bool operator<(const Matrix2& m);

		const Matrix2 operator*(real s) const;
		Matrix2& operator*=(real s);
		friend const Matrix2 operator* (real s, const Matrix2& m);

		const Matrix2 operator/(real s) const;
		Matrix2& operator/=(real s);
		friend const Matrix2 operator/ (real s, const Matrix2& m);

		const Matrix2 operator+(const Matrix2& mm) const;
		Matrix2& operator+=(const Matrix2& mm);

		const Matrix2 operator-() const;
		const Matrix2 operator-(const Matrix2& mm) const;
		Matrix2& operator-=(const Matrix2& mm);

		const Vector2D operator*(const Vector2D& v) const;
		const Matrix2 operator*(const Matrix2& mm) const;
		Matrix2& operator*=(const Matrix2& mm);

		void rotate(angle a) override;
		const angle getRotation() const override;
		const Matrix2 getRotated(angle a) const;

		void scale(const Vector2D& scale) override;
		void setScale(const Vector2D& scale) override;
		real getXScale()const override;
		real getYScale()const override;
		const Matrix2 getScaled(const Vector2D& scale) const;

		~Matrix2();
	};
}