#include <cmath>
#include <iostream>
#include "Vector2D.h"

namespace gm {

	Vector2D::Vector2D() : Vector2D(0., 0.) {}
	Vector2D::Vector2D(const coord x1, const  coord y1) : x(x1), y(y1) {}
	Vector2D::Vector2D(const int x1, const int y1) : x(x1), y(y1) {}

	const Vector2D Vector2D::addX(const coord offx) const {
		auto tmp(*this);
		tmp.x += offx;
		return tmp;
	}
	const Vector2D Vector2D::addY(const coord offy) const {
		auto tmp(*this);
		tmp.y += offy;
		return tmp;
	}
	const Vector2D Vector2D::add(const coord offx, const coord offy) const {
		return { x + offx,y + offy };
	}

	const Vector2D Vector2D::operator+(const Vector2D& u) const {
		return Vector2D::Vector2D(x + u.x, y + u.y);
	}
	const Vector2D Vector2D::operator-(const Vector2D& u) const {
		return Vector2D(x - u.x, y - u.y);
	}
	const Vector2D Vector2D::operator-()const {
		return Vector2D(-x, -y);
	}

	Vector2D& Vector2D::operator+=(const Vector2D& u) {
		x += u.x;
		y += u.y;
		return(*this);
	}
	Vector2D& Vector2D::operator-=(const Vector2D& u) {
		x -= u.x;
		y -= u.y;
		return(*this);
	}

	const Vector2D Vector2D::operator*(const coord l) const {
		return Vector2D(x * l, y * l);
	}
	const Vector2D operator*(const coord l, const Vector2D& v) {
		return v * l;
	}
	const Vector2D Vector2D::operator/(const coord l) const {
		if (l == 0 || l == (coord)-0) {
			//throw "Vector2D div by 0";
			return *this;
		}
		return Vector2D(x / l, y / l);
	}

	Vector2D& Vector2D::operator*=(const coord l) {
		x *= l;
		y *= l;
		return (*this);
	}
	Vector2D& Vector2D::operator/=(const coord l) {
		if (l == 0) {
			throw(("Vector2D : l==0"));
		}
		x /= l;
		y /= l;
		return (*this);
	}

	coord Vector2D::precision = 0.00001;
	const bool Vector2D::operator==(const Vector2D& v) const {
		return OE(x, v.x, precision) && OE(y, v.y, precision);
	}
	const bool Vector2D::operator!=(const Vector2D& v) const {
		return!((*this) == v);
	}

	const bool Vector2D::exactlyZero() const {
		return x == 0. && y == 0.;
	}

	const angle Vector2D::ang_b(const Vector2D v)const {
		if (*(*this) == 0. || *v == 0.) { return 0; }
		return acos(cosv(v)) * sign(*this % v);
	}
	const angle Vector2D::operator^(const Vector2D& v) const {
		return ang_b(v);
	}

	const Vector2D Vector2D::perpPos() const {
		return Vector2D(-y, x);
	}

	const Vector2D Vector2D::perpNeg() const {
		return Vector2D(y, -x);
	}

	const Vector2D Vector2D::operator<<(const coord angle) const {
		const double cos_ = cos(angle);
		const double sin_ = sin(angle);
		return Vector2D(x * cos_ - y * sin_, x * sin_ + y * cos_);
	}
	const Vector2D Vector2D::operator<<(Ang a) const {
		if (a == Ang::A90) {
			return Vector2D(-y, x);
		} else {
			return Vector2D(-x, -y);
		}
	}
	const Vector2D Vector2D::operator>>(const coord angle) const {
		if (!OE(angle, 0, 0.001)) {
			if (OE(angle, PI / 2)) {
				return (*this) >> Ang::A90;
			} else if (OE(angle, PI)) {
				return (*this) >> Ang::A180;
			}
			return operator<<(-angle);
		}
		return (*this);
	}
	const Vector2D Vector2D::operator>>(Ang a) const {
		if (a == Ang::A90) {
			return Vector2D(y, -x);
		}
		return Vector2D(-x, -y);
	}

	Vector2D& Vector2D::operator>>=(const coord angle) {
		return operator<<=(-angle);
	}
	Vector2D& Vector2D::operator<<=(const coord angle) {
		if (*this * *this == 0) {
			return *this;
		}
		if (OE((coord)angle, PI / 2)) {
			const auto buf = x;
			x = -y;
			y = buf;
			return *this;
		} else if (OE((coord)angle, PI)) {
			x *= -1;
			y *= -1;
			return *this;
		} else if (OE(angle, -PI / 2)) {
			const auto buf = x;
			x = y;
			y = -buf;
			return *this;
		}
		const double cos_ = cos(angle);
		const double sin_ = sin(angle);
		const auto bufx = x;
		x = x * cos_ - y * sin_;
		y = bufx * sin_ + y * cos_;
		return *this;
	}

	const Vector2D Vector2D::rot_around(const Coord2D c, const coord ang) const {
		return (((*this) - c) << ang) + c;
	}
	Vector2D& Vector2D::srot_around(const Coord2D c, const coord ang) {
		(*this) = (*this).rot_around(c, ang);
		return (*this);
	}

	const Vector2D Vector2D::to_collinear(const Vector2D v)const {
		return (*this) << ang_b(v);
	}
	Vector2D& Vector2D::sto_collinear(const Vector2D v) {
		(*this) = (*this).to_collinear(v);
		return (*this);
	}

	const Vector2D Vector2D::correct_ang(const Vector2D& c, int k_) const {
		Vector2D p = (*this);
		Vector2D vi = VI * !(p - c);
		coord ang = acos((p - c).cosv(VI));
		int k = (int)(double)(ang * k_ / PI);
		coord ang1 = k * PI / k_, ang2 = (k + 1) * PI / k_;
		if ((VI % p) > 0) {
			if (abs(ang - ang1) < abs(ang - ang2)) {
				p = c + (vi << ang1);
			} else {
				p = c + (vi << ang2);
			}
		} else {
			if (abs(ang - ang1) < abs(ang - ang2)) {
				p = c + (vi >> ang1);
			} else {
				p = c + (vi >> ang2);
			}
		}
		return p;
	}
	Vector2D& Vector2D::scorrect_ang(const Vector2D& c, int k) {
		return (*this) = correct_ang(c, k);
	}

	const Coord2D Vector2D::correct_coord(const coord step) const {
		return Coord2D(
			abs(x - (int)(x / step) * step) < step / 2 ? (int)(x / step) * step : ((int)(x / step) + sign(x)) * step,
			abs(y - (int)(y / step) * step) < step / 2 ? (int)(y / step) * step : ((int)(y / step) + sign(y)) * step);
	}
	Coord2D& Vector2D::scorrect_cord(const coord step /* = 10*/) {
		(*this) = correct_coord(step);
		return (*this);
	}

	const coord Vector2D::operator*(const Vector2D& v_) const {//ÑÊÀËßÐÍÎÅ ÏÐÎÈÇÂÅÄÅÍÈÅ ÂÅÊÒÎÐÎÂ
		return v_.x * x + v_.y * y;
	}
	const coord Vector2D::operator*() const {
		return x * x + y * y;
	}
	const coord Vector2D::operator%(const Vector2D& v)const {
		return x * v.y - y * v.x;
	}
	const coord Vector2D::cosv(const Vector2D& v) const {
		coord cos_ = (*this) * v / ((!v) * !(*this));
		if (cos_ > 1) {
			cos_ = 1;
		} else if (cos_ < -1) {
			cos_ = -1;
		}
		return cos_;
	}
	const lenght Vector2D::operator/(const Vector2D v) const {
		auto tx = x - v.x;
		auto ty = y - v.y;
		return sqrt(tx * tx + ty * ty);
	}

	const coord Vector2D::operator!() const {//ÄËÈÍÀ ÂÅÊÒÎÐÀ
		return sqrt(*(*this));
	}

	const Vector2D Vector2D::relen(const coord h) const {
		if (x != 0. || y != 0.) {
			return this->normal() * h;
		}
		return (*this);
	}
	const Vector2D Vector2D::operator()(const coord& len)const {
		return relen(len);
	}

	Vector2D& Vector2D::setLength(const coord h) {
		(*this) = relen(h);
		return*this;
	}

	const Vector2D Vector2D::normal() const {
		auto tmp = *this;
		tmp.snormal();
		return tmp;
	}
	Vector2D& Vector2D::snormal() {
		auto l = inversSquareRoot(x * x + y * y);
		x *= l;
		y *= l;
		return*this;
	}
	Vector2D& Vector2D::operator[](const coord& h) {
		return setLength(h);
	}

	Vector2D& Vector2D::limit(const lenght& bottom, const lenght& top) {
		auto l = operator*();
		if (l > top * top) {
			setLength(top);
		} else if (l < bottom * bottom) {
			setLength(bottom);
		}
		return *this;
	}

	Vector2D& Vector2D::limitTop(const lenght& top) {
		auto l = operator*();
		if (l > top * top) {
			setLength(top);
		}
		return *this;
	}

	Vector2D& Vector2D::limitBottom(const lenght& bottom) {
		auto l = operator*();
		if (l < bottom * bottom) {
			setLength(bottom);
		}
		return *this;
	}

	const Vector2D Vector2D::add_len(const lenght& l) const {
		auto tmp = *this;
		tmp.sadd_len(l);
		return tmp;
	}
	Vector2D& Vector2D::sadd_len(const lenght& l) {
		return setLength(operator!() + l);
	}

	const Vector2D Vector2D::invX() const {
		return Vector2D(-x, y);
	}
	const Vector2D Vector2D::invY() const {
		return Vector2D(x, -y);
	}
	const Vector2D Vector2D::vecX() const {
		return Vector2D(x, 0.);
	}
	const Vector2D Vector2D::vecY() const {
		return Vector2D(0., y);
	}


	//ââîä / âûâîä
	std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		out << std::fixed;
		out.precision(1);
		out << "(" << v.x << "; " << v.y << ")";
		return out;
	}
	std::istream& operator>>(std::istream& in, Vector2D& v) {
		in >> v.x >> v.y;
		return in;
	}


	//SFML Support
#ifdef SFML_VECTOR2_HPP
	Vector2D::Vector2D(const sf::Vector2f& v) : x{ v.x }, y{ v.y }{}
	Vector2D::Vector2D(const sf::Vector2i& v) : x(static_cast<coord>(v.x)), y(static_cast<coord>(v.y)) {}
	Vector2D::Vector2D(const sf::Vector2u& v) : x(static_cast<coord>(v.x)), y(static_cast<coord>(v.y)) {}
	Vector2D::operator sf::Vector2f()const {
		return sf::Vector2f{ static_cast<float> (x),static_cast<float>(y) };
	}
	Vector2D::operator sf::Vector2i()const {
		return sf::Vector2i{ static_cast<int> (x),static_cast<int>(y) };
	}
	Vector2D::operator sf::Vector2u() const {
		return sf::Vector2u{ static_cast<unsigned> (x),static_cast<unsigned>(y) };
	}
#endif


	//nlohman Support
#ifdef INCLUDE_NLOHMANN_JSON_HPP_
	Vector2D::Vector2D(const json& vjson) :
		x(vjson["x"].get<double>()), y(vjson["y"].get<double>()) {}
	const json Vector2D::convertToJSON(const str xname, const str yname) const {
		return { {xname,x}, {yname,y} };
	}
	const json Vector2D::convertVectorToJSON() const {
		return convertToJSON("x", "y");
	}
	const json Vector2D::convertSizeToJSON() const {
		return convertToJSON("w", "h");
	}
	void Vector2D::insertToJSON(
		json& obj,
		const str xname,
		const str yname) {
		obj[xname] = x;
		obj[yname] = y;
	}
	void Vector2D::insertVectorToJSON(json& obj) {
		insertToJSON(obj, "x", "y");
	}
	void Vector2D::insertSizeToJSON(json& obj) {
		insertToJSON(obj, "w", "h");
	}
#endif
}