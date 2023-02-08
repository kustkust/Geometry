#include <cmath>
#include <iostream>
#include "Vector.h"

namespace gm {

	Vector::Vector() : Vector(0., 0.) {}
	Vector::Vector(const coord x1, const  coord y1) : x(x1), y(y1) {}
	Vector::Vector(const int x1, const int y1) : x(x1), y(y1) {}

	const Vector Vector::addX(const coord offx) const {
		auto tmp(*this);
		tmp.x += offx;
		return tmp;
	}
	const Vector Vector::addY(const coord offy) const {
		auto tmp(*this);
		tmp.y += offy;
		return tmp;
	}
	const Vector Vector::add(const coord offx, const coord offy) const {
		return { x + offx,y + offy };
	}

	const Vector Vector::operator+(const Vector& u) const {
		return Vector::Vector(x + u.x, y + u.y);
	}
	const Vector Vector::operator-(const Vector& u) const {
		return Vector(x - u.x, y - u.y);
	}
	const Vector Vector::operator-()const {
		return Vector(-x, -y);
	}

	Vector& Vector::operator+=(const Vector& u) {
		x += u.x;
		y += u.y;
		return(*this);
	}
	Vector& Vector::operator-=(const Vector& u) {
		x -= u.x;
		y -= u.y;
		return(*this);
	}

	const Vector Vector::operator*(const coord l) const {
		return Vector(x * l, y * l);
	}
	const Vector operator*(const coord l, const Vector& v) {
		return v * l;
	}
	const Vector Vector::operator/(const coord l) const {
		if (l == 0 || l == (coord)-0) {
			//throw "Vector div by 0";
			return *this;
		}
		return Vector(x / l, y / l);
	}

	Vector& Vector::operator*=(const coord l) {
		x *= l;
		y *= l;
		return (*this);
	}
	Vector& Vector::operator/=(const coord l) {
		if (l == 0) {
			throw(("Vector : l==0"));
		}
		x /= l;
		y /= l;
		return (*this);
	}

	coord Vector::precision = 0.00001;
	const bool Vector::operator==(const Vector& v) const {
		return OE(x, v.x, precision) && OE(y, v.y, precision);
	}
	const bool Vector::operator!=(const Vector& v) const {
		return!((*this) == v);
	}

	const bool Vector::exactlyZero() const {
		return x == 0. && y == 0.;
	}

	const angle Vector::ang_b(const Vector v)const {
		// if (*(*this) == 0. || *v == 0.) { return 0; }
		// return acos(cosv(v)) * sign(*this % v);
		auto a = atan2(v.y, v.x) - atan2(y, x);
		return 
			a > PI ? a - PI2 :
			a < -PI ? a + PI2 : 
			a;
	}
	const angle Vector::operator^(const Vector& v) const {
		return ang_b(v);
	}

	const Vector Vector::perpPos() const {
		return Vector(-y, x);
	}

	const Vector Vector::perpNeg() const {
		return Vector(y, -x);
	}

	const Vector Vector::operator<<(const coord angle) const {
		const double cos_ = cos(angle);
		const double sin_ = sin(angle);
		return Vector(x * cos_ - y * sin_, x * sin_ + y * cos_);
	}
	const Vector Vector::operator<<(Ang a) const {
		if (a == Ang::A90) {
			return Vector(-y, x);
		} else {
			return Vector(-x, -y);
		}
	}
	const Vector Vector::operator>>(const coord angle) const {
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
	const Vector Vector::operator>>(Ang a) const {
		if (a == Ang::A90) {
			return Vector(y, -x);
		}
		return Vector(-x, -y);
	}

	Vector& Vector::operator>>=(const coord angle) {
		return operator<<=(-angle);
	}
	Vector& Vector::operator<<=(const coord angle) {
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

	const Vector Vector::rot_around(const Coord c, const coord ang) const {
		return (((*this) - c) << ang) + c;
	}
	Vector& Vector::srot_around(const Coord c, const coord ang) {
		(*this) = (*this).rot_around(c, ang);
		return (*this);
	}

	const Vector Vector::to_collinear(const Vector v)const {
		return (*this) << ang_b(v);
	}
	Vector& Vector::sto_collinear(const Vector v) {
		(*this) = (*this).to_collinear(v);
		return (*this);
	}

	const Vector Vector::correct_ang(const Vector& c, int k_) const {
		Vector p = (*this);
		Vector vi = VI * !(p - c);
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
	Vector& Vector::scorrect_ang(const Vector& c, int k) {
		return (*this) = correct_ang(c, k);
	}

	const Coord Vector::correct_coord(const coord step) const {
		return Coord(
			abs(x - (int)(x / step) * step) < step / 2 ? (int)(x / step) * step : ((int)(x / step) + sign(x)) * step,
			abs(y - (int)(y / step) * step) < step / 2 ? (int)(y / step) * step : ((int)(y / step) + sign(y)) * step);
	}
	Coord& Vector::scorrect_cord(const coord step /* = 10*/) {
		(*this) = correct_coord(step);
		return (*this);
	}

	const coord Vector::operator*(const Vector& v_) const {//ÑÊÀËßÐÍÎÅ ÏÐÎÈÇÂÅÄÅÍÈÅ ÂÅÊÒÎÐÎÂ
		return v_.x * x + v_.y * y;
	}
	const coord Vector::operator*() const {
		return x * x + y * y;
	}
	const coord Vector::operator%(const Vector& v)const {
		return x * v.y - y * v.x;
	}
	const coord Vector::cosv(const Vector& v) const {
		coord cos_ = (*this) * v / ((!v) * !(*this));
		if (cos_ > 1) {
			cos_ = 1;
		} else if (cos_ < -1) {
			cos_ = -1;
		}
		return cos_;
	}
	const lenght Vector::operator/(const Vector v) const {
		auto tx = x - v.x;
		auto ty = y - v.y;
		return sqrt(tx * tx + ty * ty);
	}

	const coord Vector::operator!() const {//ÄËÈÍÀ ÂÅÊÒÎÐÀ
		return sqrt(*(*this));
	}

	const Vector Vector::relen(const coord h) const {
		if (x != 0. || y != 0.) {
			return this->normal() * h;
		}
		return (*this);
	}
	const Vector Vector::operator()(const coord& len)const {
		return relen(len);
	}

	Vector& Vector::setLength(const coord h) {
		(*this) = relen(h);
		return*this;
	}

	const Vector Vector::normal() const {
		auto tmp = *this;
		tmp.snormal();
		return tmp;
	}
	Vector& Vector::snormal() {
		auto l = inversSquareRoot(x * x + y * y);
		x *= l;
		y *= l;
		return*this;
	}
	Vector& Vector::operator[](const coord& h) {
		return setLength(h);
	}

	Vector& Vector::limit(const lenght& bottom, const lenght& top) {
		auto l = operator*();
		if (l > top * top) {
			setLength(top);
		} else if (l < bottom * bottom) {
			setLength(bottom);
		}
		return *this;
	}

	Vector& Vector::limitTop(const lenght& top) {
		auto l = operator*();
		if (l > top * top) {
			setLength(top);
		}
		return *this;
	}

	Vector& Vector::limitBottom(const lenght& bottom) {
		auto l = operator*();
		if (l < bottom * bottom) {
			setLength(bottom);
		}
		return *this;
	}

	const Vector Vector::add_len(const lenght& l) const {
		auto tmp = *this;
		tmp.sadd_len(l);
		return tmp;
	}
	Vector& Vector::sadd_len(const lenght& l) {
		return setLength(operator!() + l);
	}

	const Vector Vector::invX() const {
		return Vector(-x, y);
	}
	const Vector Vector::invY() const {
		return Vector(x, -y);
	}
	const Vector Vector::vecX() const {
		return Vector(x, 0.);
	}
	const Vector Vector::vecY() const {
		return Vector(0., y);
	}


	//ââîä / âûâîä
	std::ostream& operator<<(std::ostream& out, const Vector& v) {
		out << std::fixed;
		out.precision(1);
		out << "(" << v.x << "; " << v.y << ")";
		return out;
	}
	std::istream& operator>>(std::istream& in, Vector& v) {
		in >> v.x >> v.y;
		return in;
	}


	//SFML Support
#ifdef SFML_VECTOR2_HPP
	Vector::Vector(const sf::Vector2f& v) : x{ v.x }, y{ v.y }{}
	Vector::Vector(const sf::Vector2i& v) : x(static_cast<coord>(v.x)), y(static_cast<coord>(v.y)) {}
	Vector::Vector(const sf::Vector2u& v) : x(static_cast<coord>(v.x)), y(static_cast<coord>(v.y)) {}
	Vector::operator sf::Vector2f()const {
		return sf::Vector2f{ static_cast<float> (x),static_cast<float>(y) };
	}
	Vector::operator sf::Vector2i()const {
		return sf::Vector2i{ static_cast<int> (x),static_cast<int>(y) };
	}
	Vector::operator sf::Vector2u() const {
		return sf::Vector2u{ static_cast<unsigned> (x),static_cast<unsigned>(y) };
	}
#endif


	//nlohman Support
#ifdef INCLUDE_NLOHMANN_JSON_HPP_
	Vector::Vector(const json& vjson) :
		x(vjson["x"].get<double>()), y(vjson["y"].get<double>()) {}
	const json Vector::convertToJSON(const str xname, const str yname) const {
		return { {xname,x}, {yname,y} };
	}
	const json Vector::convertVectorToJSON() const {
		return convertToJSON("x", "y");
	}
	const json Vector::convertSizeToJSON() const {
		return convertToJSON("w", "h");
	}
	void Vector::insertToJSON(
		json& obj,
		const str xname,
		const str yname) {
		obj[xname] = x;
		obj[yname] = y;
	}
	void Vector::insertVectorToJSON(json& obj) {
		insertToJSON(obj, "x", "y");
	}
	void Vector::insertSizeToJSON(json& obj) {
		insertToJSON(obj, "w", "h");
	}
#endif
}