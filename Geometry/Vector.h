#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>
#include <iostream>
#include "Geometry.def.h"
namespace gm {

	using PointsArray = std::vector<Vector>;

	class Vector {
	public:
		coord x, y;
		Vector();
		Vector(const coord x1, const  coord y1);
		Vector(const int x1, const int y1);

		const Vector operator+(const Vector& u) const;
		const Vector operator-(const Vector& u) const;
		const Vector operator-()const;

		Vector& operator+=(const Vector& u);
		Vector& operator-=(const Vector& u);

		const Vector operator*(const coord l) const;
		friend const Vector operator*(const coord l, const Vector& v);
		const Vector operator/(const coord l) const;

		Vector& operator*=(const coord l);
		Vector& operator/=(const coord l);

		static coord precision;
		const bool operator==(const Vector& v) const;
		const bool operator!=(const Vector& v) const;
		const bool exactlyZero()const;

		const angle ang_b(const Vector v) const;
		const angle operator^(const Vector& v) const;

		const Vector perpPos()const;
		const Vector perpNeg()const;

		const Vector operator<<(const coord angle) const;
		const Vector operator<<(Ang a) const;
		const Vector operator>>(const coord angle) const;
		const Vector operator>>(Ang a) const;

		Vector& operator<<=(const coord angle);
		Vector& operator>>=(const coord angle);

		const Vector rot_around(const Coord c, const coord ang) const;
		Vector& srot_around(const Coord c, const coord ang);

		const Vector to_collinear(const Vector v) const;
		Vector& sto_collinear(const Vector v);

		const Vector correct_ang(const Vector& c = Vector(0, 0), int k = 8) const;
		Vector& scorrect_ang(const Vector& c, int k = 8);

		const Coord correct_coord(const coord step = 10) const;
		Coord& scorrect_cord(const coord step = 10);

		const coord operator*(const Vector& v) const;
		const coord operator*()const;
		const coord operator%(const Vector& v) const;
		const coord cosv(const Vector& v) const;
		const lenght operator/(const Vector v) const;

		const coord operator!() const;

		const Vector relen(const coord h) const;
		const Vector operator()(const coord& len) const;

		Vector& setLength(const coord h);
		Vector& operator[](const coord& h);

		Vector& limit(const lenght& bottom, const lenght& top);
		Vector& limitTop(const lenght& top);
		Vector& limitBottom(const lenght& bottom);

		const Vector normal() const;
		Vector& snormal();

		const Vector add_len(const lenght& l) const;
		Vector& sadd_len(const lenght& l);


		const Vector addX(const coord offx) const;
		const Vector addY(const coord offy) const;
		const Vector add(const coord offx, const coord offy) const;
		const Vector mulX(const real mx) const;
		const Vector mulY(const real my) const;
		const Vector mul(real mx, real my) const;
		const Vector mul(const gm::Vector& m) const;
		const Vector invX() const;
		const Vector invY() const;
		const Vector vecX() const;
		const Vector vecY() const;

		//ввод / вывод
		friend std::ostream& operator<<(std::ostream& out, const Vector& v);
		friend std::istream& operator>>(std::istream& in, Vector& v);

		//SFML Support
#ifdef SFML_VECTOR2_HPP
		Vector(const sf::Vector2f& v);
		Vector(const sf::Vector2i& v);
		Vector(const sf::Vector2u& v);

		operator sf::Vector2f() const;
		operator sf::Vector2i() const;
		operator sf::Vector2u() const;

		template<class T>
		const Vector operator+(const sf::Vector2<T>& u) const {
			return Vector(x + u.x, y + u.y);
		}
		template<class T>
		friend const Vector operator+(const sf::Vector2<T>& u, const Vector& v) {
			return Vector(u.x + v.x, u.y + v.y);
		}
		template<class T>
		const Vector operator-(const sf::Vector2<T>& u) const {
			return Vector(x - u.x, y - u.y);
		}
		template<class T>
		friend const Vector operator-(const sf::Vector2<T>& u, const Vector& v) {
			return Vector(u.x - v.x, u.y - v.y);
		}

		template<class T>
		Vector& operator+=(const sf::Vector2<T>& u) {
			x += u.x;
			y += u.y;
			return *this;
		}
		template<class T>
		Vector& operator-=(const sf::Vector2<T>& u) {
			x -= u.x;
			y -= u.y;
			return *this;
		}
#endif // SFML_VECTOR2_HPP

		//nlohman Support
#ifdef INCLUDE_NLOHMANN_JSON_HPP__
		Vector(const json& vjson);
		Vector(const int& i) = delete;
		Vector(const std::string& s) = delete;
		Vector(const char& s) = delete;
		Vector(const float& f) = delete;
		Vector(const double& f) = delete;

		const json convertToJSON(const std::string xname, const std::string yname) const;
		const json convertVectorToJSON() const;
		const json convertSizeToJSON() const;

		void insertToJSON(json& obj, const std::string xname, const std::string yname);
		void insertVectorToJSON(json& obj);
		void insertSizeToJSON(json& obj);
#endif // INCLUDE_NLOHMANN_JSON_HPP__

	};

	const Vector VI(1, 0);
	const Vector VX(1, 0);
	const Vector VJ(0, 1);
	const Vector VY(0, 1);
	const Vector VIJ(1, 1);
	const Vector VXY(1, 1);
	const Vector NV(0, 0);
	const Vector VN(0, 0);
}