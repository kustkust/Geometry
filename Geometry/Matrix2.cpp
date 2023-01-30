#include "Matrix2.h"
#include "Vector2D.h"

namespace gm {
	Matrix2::Matrix2() :m{ 1,0,0,1 } {}
	Matrix2::Matrix2(const Matrix2& _m) : m{ _m.m[0],_m.m[1], _m.m[2], _m.m[3], } {}
	Matrix2::Matrix2(Matrix2&& _m) noexcept { std::swap(m, _m.m); }
	Matrix2::Matrix2(angle a) : m{ cos(a), -sin(a), sin(a), cos(a) } {}
	Matrix2::Matrix2(real m11, real m12, real m21, real m22) : m{ m11,m12,m21,m22 } {}
	Matrix2::Matrix2(real _m[4]) : m{ _m[0], _m[1], _m[2], _m[3] } {}

	Matrix2& Matrix2::operator=(const Matrix2& _m) {
		m[0] = _m.m[0];
		m[1] = _m.m[1];
		m[2] = _m.m[2];
		m[3] = _m.m[3];
		return *this;
	}

	Matrix2& Matrix2::operator=(Matrix2&& _m) noexcept {
		std::swap(m, _m.m);
		return *this;
	}

	bool Matrix2::operator==(const Matrix2& _m) {
		return OE(m[0], _m.m[0]) && OE(m[1], _m.m[1]) && OE(m[2], _m.m[2]) && OE(m[3], _m.m[3]);
	}

	bool Matrix2::operator<(const Matrix2& _m) {
		return
			m[0] != _m.m[0] ? m[0] < _m.m[0] :
			m[1] != _m.m[1] ? m[1] < _m.m[1] :
			m[2] != _m.m[2] ? m[2] < _m.m[2] :
			m[3] != _m.m[3] ? m[3] < _m.m[3] :
			false;
	}


	const Matrix2 Matrix2::operator*(real s) const {
		Matrix2 tmp = *this;
		tmp *= s;
		return tmp;
	}

	Matrix2& Matrix2::operator*=(real s) {
		m[0] *= s;
		m[1] *= s;
		m[2] *= s;
		m[3] *= s;
		return *this;
	}

	const Matrix2 Matrix2::operator/(real s) const {
		Matrix2 tmp = *this;
		tmp /= s;
		return tmp;
	}

	Matrix2& Matrix2::operator/=(real s) {
		m[0] /= s;
		m[1] /= s;
		m[2] /= s;
		m[3] /= s;
		return *this;
	}

	const Matrix2 Matrix2::operator+(const Matrix2& _m) const {
		Matrix2 tmp = *this;
		tmp *= _m;
		return tmp;
	}

	Matrix2& Matrix2::operator+=(const Matrix2& _m) {
		m[0] += _m.m[0];
		m[0] += _m.m[0];
		m[0] += _m.m[0];
		m[0] += _m.m[0];
		return *this;
	}

	const Matrix2 Matrix2::operator-() const {
		return Matrix2(-m[0], -m[1], -m[2], -m[3]);
	}

	const Matrix2 Matrix2::operator-(const Matrix2& _m) const {
		Matrix2 tmp = *this;
		tmp -= _m;
		return tmp;
	}

	Matrix2& Matrix2::operator-=(const Matrix2& _m) {
		m[0] -= _m.m[0];
		m[0] -= _m.m[0];
		m[0] -= _m.m[0];
		m[0] -= _m.m[0];
		return *this;
	}

	const Matrix2 operator*(real s, const Matrix2& m) {
		return Matrix2(s * m.m[0], s * m.m[1], s * m.m[2], s * m.m[3]);
	}

	const Matrix2 operator/(real s, const Matrix2& m) {
		return Matrix2(s / m.m[0], s / m.m[1], s / m.m[2], s / m.m[3]);
	}

	const Vector2D Matrix2::operator*(const Vector2D& v) const {
		return Vector2D(m[0] * v.x + m[1] * v.y, m[2] * v.x + m[3] * v.y);
	}

	const Matrix2 Matrix2::operator*(const Matrix2& _m) const {
		return {
			m[0] * _m.m[0] + m[1] * _m.m[2],
			m[0] * _m.m[1] + m[1] * _m.m[3],
			m[2] * _m.m[0] + m[3] * _m.m[2],
			m[2] * _m.m[1] + m[3] * _m.m[3],
		};
	}

	Matrix2& Matrix2::operator*=(const Matrix2& _m) {
		*this = (*this) * _m;
		return *this;
	}

	void Matrix2::rotate(angle a) {
		(*this) *= Matrix2(a);
	}

	const angle Matrix2::getRotation() const {
		auto xScale = getXScale();
		auto coss = m[0] / xScale, sinn = m[1] / xScale;
		return atan2(sinn, coss);
	}

	const Matrix2 Matrix2::getRotated(angle a) const {
		return (*this) * Matrix2(a);
	}

	void Matrix2::scale(const Vector2D& scale) {
		m[0] *= scale.x;
		m[1] *= scale.x;
		m[2] *= scale.y;
		m[3] *= scale.y;
	}

	void Matrix2::setScale(const Vector2D& scale) {
		auto newXScale = scale.x / getXScale(), newYScale = scale.y / getYScale();
		m[0] *= newXScale;
		m[1] *= newXScale;
		m[2] *= newYScale;
		m[3] *= newYScale;
	}

	real Matrix2::getXScale() const {
		return sqrt(m[0] * m[0] + m[1] * m[1]);
	}

	real Matrix2::getYScale() const {
		return sqrt(m[2] * m[2] + m[3] * m[3]);
	}

	const Matrix2 Matrix2::getScaled(const Vector2D& scale) const {
		auto newXScale = scale.x / getXScale(), newYScale = scale.y / getYScale();
		return {
			m[0] * newXScale,
			m[1] * newXScale,
			m[2] * newYScale,
			m[3] * newYScale,
		};
	}

	Matrix2::~Matrix2()
	{
	}

}