#pragma once
#include <memory>
#include <array>
#include "Vector.h"

namespace gm {
	class ICollison {
	public:
		ICollison() = default;
		virtual operator bool() const = 0;
		virtual PointsArray getPoints() const = 0;
		virtual ~ICollison() {}
	};

	class SimpleCollision : public ICollison {
		bool collide = false;
		Coord coll;
	public:
		SimpleCollision() = default;
		SimpleCollision(SimpleCollision&&) = default;
		SimpleCollision(const SimpleCollision&) = default;
		SimpleCollision& operator=(SimpleCollision&&) = default;
		SimpleCollision& operator=(const SimpleCollision&) = default;

		SimpleCollision(const Coord& collide) : coll(collide), collide(true) {}
		SimpleCollision& operator=(bool b) {
			collide = b;
			return *this;
		}
		operator bool() const override {
			return collide;
		}
		virtual PointsArray getPoints() const override {
			if (collide) {
				return { coll };
			}
			return {};
		}
	};

	class Collision : public ICollison {
		using Cptr = std::unique_ptr<ICollison>;
		Cptr collision;
	public:
		Collision() = default;
		Collision(Collision&&) = default;
		Collision(const Collision&) = default;
		Collision& operator=(Collision&&) = default;
		Collision& operator=(const Collision&) = default;

		template<class T, class... Args>
		Collision(Args&&... args) : collision(std::make_unique<T>(std::forward<Args>(args)...)) {

		}
		Collision(Cptr&& coll) : collision(std::forward<Cptr>(coll)) {

		}
		Collision& operator=(Cptr&& ptr) {
			collision = std::forward<Cptr>(ptr);
		}

		operator bool() const override {
			return collision ? collision->operator bool() : false;
		}
		virtual PointsArray getPoints() const override {
			return collision->getPoints();
		}
		ICollison* operator*() {
			return collision.get();
		}
		const ICollison* operator*() const {
			return collision.get();
		}
	};

	template<class T, class... Args>
	Collision makeCollision(Args&&... args) {
		return Collision(std::make_unique<T>(std::forward<Args>(args)...));
	}

	class PointsColl2 : public ICollison {
		std::array<Coord, 2> colP;
		int count = 0;
		bool collide = false;
	public:
		PointsColl2() = default;
		PointsColl2(PointsColl2&&) = default;
		PointsColl2(const PointsColl2&) = default;
		PointsColl2& operator=(PointsColl2&&) = default;
		PointsColl2& operator=(const PointsColl2&) = default;

		PointsColl2(bool collide) : 
			collide(collide) {}
		PointsColl2(const Coord& p) : 
			colP({ p,{} }), count(1), collide(true) {}
		PointsColl2(const Coord& p1, const Coord& p2) : 
			colP({ p1,p2 }), count(2), collide(true) {}

		operator bool()const override {
			return collide;
		}
		virtual PointsArray getPoints() const override {
			if (count == 1) {
				return { colP[0] };
			}
			if (count == 2) {
				return { colP[0], colP[1] };
			}
			return {};
		}
		int getCount() {
			return count;
		}
		const Coord getFirst() {
			return colP[0];
		}
		const Coord getSecond() {
			return colP[1];
		}
	};

	class PointsColl : public ICollison {
		std::vector<Coord> colP;
		bool collide = false;
	public:
		PointsColl() = default;
		PointsColl(PointsColl&&) = default;
		PointsColl(const PointsColl&) = default;
		PointsColl& operator=(PointsColl&&) = default;
		PointsColl& operator=(const PointsColl&) = default;

		PointsColl(bool collide) :
			collide(collide) {}
		PointsColl(const Coord& p) :
			colP({ p,{} }), collide(true) {}
		PointsColl(const Coord& p1, const Coord& p2) :
			colP({ p1,p2 }), collide(true) {}
		PointsColl(const std::initializer_list<Coord>& ps) :
			colP(ps), collide(true) {}
		PointsColl(const std::vector<Coord>& ps) :
			colP(ps), collide(true) {}
		PointsColl(std::vector<Coord>&& ps) :
			colP(std::forward<std::vector<Coord>>(ps)), collide(true) {}

		operator bool()const override {
			return collide;
		}
		virtual PointsArray getPoints() const override {
			return colP;
		}
		int getCount() {
			return int(colP.size());
		}
		const Coord getFirst() {
			return colP[0];
		}
		const Coord getSecond() {
			return colP[1];
		}
	};
}