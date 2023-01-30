#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>
#include <iostream>
#include "Geometry.def.h"
namespace gm {

	using PointsArray = std::vector<Vector2D>;

	class Vector2D {
	public:
		coord x, y;
		Vector2D();
		Vector2D(const coord x1, const  coord y1);
		Vector2D(const int x1, const int y1);

		const Vector2D addX(const coord offx) const;
		const Vector2D addY(const coord offy) const;
		const Vector2D add(const coord offx, const coord offy) const;

		const Vector2D operator+(const Vector2D& u) const;
		const Vector2D operator-(const Vector2D& u) const;
		const Vector2D operator-()const;

		Vector2D& operator+=(const Vector2D& u);
		Vector2D& operator-=(const Vector2D& u);

		const Vector2D operator*(const coord l) const;
		friend const Vector2D operator*(const coord l, const Vector2D& v);
		const Vector2D operator/(const coord l) const;

		Vector2D& operator*=(const coord l);
		Vector2D& operator/=(const coord l);

		static coord precision;
		const bool operator==(const Vector2D& v) const;
		const bool operator!=(const Vector2D& v) const;
		const bool exactlyZero()const;

		const angle ang_b(const Vector2D v) const;
		const angle operator^(const Vector2D& v) const;

		const Vector2D perpPos()const;
		const Vector2D perpNeg()const;

		const Vector2D operator<<(const coord angle) const;
		const Vector2D operator<<(Ang a) const;
		const Vector2D operator>>(const coord angle) const;
		const Vector2D operator>>(Ang a) const;

		Vector2D& operator<<=(const coord angle);
		Vector2D& operator>>=(const coord angle);

		const Vector2D rot_around(const Coord2D c, const coord ang) const;
		Vector2D& srot_around(const Coord2D c, const coord ang);

		const Vector2D to_collinear(const Vector2D v) const;
		Vector2D& sto_collinear(const Vector2D v);

		const Vector2D correct_ang(const Vector2D& c = Vector2D(0, 0), int k = 8) const;
		Vector2D& scorrect_ang(const Vector2D& c, int k = 8);

		const Coord2D correct_coord(const coord step = 10) const;
		Coord2D& scorrect_cord(const coord step = 10);

		const coord operator*(const Vector2D& v) const;
		const coord operator*()const;
		const coord operator%(const Vector2D& v) const;
		const coord cosv(const Vector2D& v) const;
		const lenght operator/(const Vector2D v) const;

		const coord operator!() const;

		const Vector2D relen(const coord h) const;
		const Vector2D operator()(const coord& len) const;

		Vector2D& setLength(const coord h);
		Vector2D& operator[](const coord& h);

		Vector2D& limit(const lenght& bottom, const lenght& top);
		Vector2D& limitTop(const lenght& top);
		Vector2D& limitBottom(const lenght& bottom);

		const Vector2D normal() const;
		Vector2D& snormal();

		const Vector2D add_len(const lenght& l) const;
		Vector2D& sadd_len(const lenght& l);

		const Vector2D invX() const;
		const Vector2D invY() const;
		const Vector2D vecX() const;
		const Vector2D vecY() const;

		//ввод / вывод
		friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
		friend std::istream& operator>>(std::istream& in, Vector2D& v);

		//SFML Support
#ifdef SFML_VECTOR2_HPP
		Vector2D(const sf::Vector2f& v);
		Vector2D(const sf::Vector2i& v);
		Vector2D(const sf::Vector2u& v);

		operator sf::Vector2f() const;
		operator sf::Vector2i() const;
		operator sf::Vector2u() const;

		template<class T>
		const Vector2D operator+(const sf::Vector2<T>& u) const {
			return Vector2D(x + u.x, y + u.y);
		}
		template<class T>
		friend const Vector2D operator+(const sf::Vector2<T>& u, const Vector2D& v) {
			return Vector2D(u.x + v.x, u.y + v.y);
		}
		template<class T>
		const Vector2D operator-(const sf::Vector2<T>& u) const {
			return Vector2D(x - u.x, y - u.y);
		}
		template<class T>
		friend const Vector2D operator-(const sf::Vector2<T>& u, const Vector2D& v) {
			return Vector2D(u.x - v.x, u.y - v.y);
		}

		template<class T>
		Vector2D& operator+=(const sf::Vector2<T>& u) {
			x += u.x;
			y += u.y;
			return *this;
		}
		template<class T>
		Vector2D& operator-=(const sf::Vector2<T>& u) {
			x -= u.x;
			y -= u.y;
			return *this;
		}
#endif // SFML_VECTOR2_HPP

		//nlohman Support
#ifdef INCLUDE_NLOHMANN_JSON_HPP_
		Vector2D(const json& vjson);
		Vector2D(const int& i) = delete;
		Vector2D(const str& s) = delete;
		Vector2D(const char& s) = delete;
		Vector2D(const float& f) = delete;
		Vector2D(const double& f) = delete;

		const json convertToJSON(const str xname, const str yname) const;
		const json convertVectorToJSON() const;
		const json convertSizeToJSON() const;

		void insertToJSON(json& obj, const str xname, const str yname);
		void insertVectorToJSON(json& obj);
		void insertSizeToJSON(json& obj);
#endif // INCLUDE_NLOHMANN_JSON_HPP_

	};

	const Vector2D VI(1, 0);
	const Vector2D VX(1, 0);
	const Vector2D VJ(0, 1);
	const Vector2D VY(0, 1);
	const Vector2D VIJ(1, 1);
	const Vector2D VXY(1, 1);
	const Vector2D NV(0, 0);
	const Vector2D VN(0, 0);
}