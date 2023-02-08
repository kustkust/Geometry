#include <limits>
#include "Circle.h"
#include "Rectangle.h"
using namespace gm;

const Vector Circle::getV()const {
	return Vector(center.x, center.y + radius);
}
Circle::Circle(Coord center, coord radius) : center(center), radius(radius) {}
Circle::Circle() :Circle(NV, 1) {

}

void Circle::resize(const Coord& p) {
	radius = !(p - center);
}

void gm::Circle::scale(const Vector& scale) {
	radius *= scale.x;
#ifdef _DEBUG
	if (scale.x != scale.y) {
		std::cout << "Circle::scale() : x and y must be equale" << std::endl;
	}
#endif
}

const Vector gm::Circle::getScale() const {
	return Vector(1, 1);
}

void gm::Circle::move(const Vector& v) {
	center += v;
}

const Coord gm::Circle::getPosition() const {
	return center;
}

const Coord gm::Circle::getCenter() const {
	return center;
}

void gm::Circle::setCenter(const Coord& pos) {
	center = pos;
}

const Size gm::Circle::getSize() const {
	return Size(radius * 2, radius * 2);
}

const Coord gm::Circle::getLeftTop() const {
	return center - gm::Vector(radius, radius);
}

void gm::Circle::setLeftTop(const Coord& lt) {
	center = lt + Vector(radius, radius);
}

void gm::Circle::setSize(const gm::Size& newSize) {
	radius = newSize.x / 2;
#ifdef _DEBUG
	if (newSize.x != newSize.y) {
		std::cout << "Circle::setSize() : x and y must be equale" << std::endl;
	}
#endif
}

// inside
bool gm::Circle::inside(const Line& other) const { // V
	return false;
}

bool gm::Circle::inside(const Sect& other) const { // V
	return false;
}

bool gm::Circle::inside(const Circle& other) const { // V
	return center / other.center + radius < other.radius;
}

bool gm::Circle::inside(const Rectangle& other) const { // V
	return getBounds().inside(other);
}

// outside
bool gm::Circle::outside(const Line& other) const { // V
	return abs(other / center) >= radius;
}

bool gm::Circle::outside(const Sect& other) const { // V
	return !contains(other.p0) && !contains(other.p1);
}

bool gm::Circle::outside(const Circle& other) const { // V
	return center / other.center > radius + other.radius;
}

bool gm::Circle::outside(const Rectangle& other) const { // V
	if (center.x >= other.getLeft() && center.x <= other.getRight()) {
		return center.y + radius <= other.getTop() || center.y - radius >= other.getBottom();
	} else if (center.y >= other.getTop() && center.y <= other.getBottom()) {
		return center.x + radius <= other.getLeft() || center.x - radius >= other.getRight();
	} else {
		return
			center / other.getLeftTop() >= radius &&
			center / other.getRightTop() >= radius &&
			center / other.getLeftBottom() >= radius &&
			center / other.getRightBottom() >= radius;
	}
}

// collides
Collision gm::Circle::collides(const Line& l) const { // V
	coord h = l / center;
	if (OE(abs(h), radius)) {
		return makeCollision<PointsColl2>(center - l.n.relen(h));
	} else if (abs(h) > radius) {
		return makeCollision<PointsColl2>(false);
	} else if (abs(h) < radius) {
		const Coord ans = center - l.n(h);
		const coord d = sqrt(radius * radius - h * h);
		return makeCollision<PointsColl2>(
			ans + (l.n >> Ang::A90).relen(d),
			ans + (l.n << Ang::A90).relen(d)
			);
	}
	return makeCollision<PointsColl2>(false);
}

Collision gm::Circle::collides(const Sect& l) const { // V
	auto coll = collides(Line(l.p0, l.p1));
	auto pc2 = dynamic_cast<PointsColl2*>(*coll);
	if (pc2->getCount() == 1 && l.between(pc2->getFirst())) {
		return makeCollision<PointsColl2>(pc2->getFirst());
	} else if (pc2->getCount() == 2) {
		Coord ps[2];
		int i = 0;
		if (l.between(pc2->getFirst())) {
			ps[i++] = pc2->getFirst();
		}
		if (l.between(pc2->getSecond())) {
			ps[i++] = pc2->getSecond();
		}
		if (i == 0) {
			return makeCollision<PointsColl2>(true);
		} else if (i == 1) {
			return makeCollision<PointsColl2>(ps[0]);
		} else if (i == 2) {
			return makeCollision<PointsColl2>(ps[0], ps[1]);
		}
	}
	return makeCollision<PointsColl2>(false);
}

Collision gm::Circle::collides(const Circle& other) const { // V
	if (inside(other) || other.inside(*this)) {
		return makeCollision<PointsColl>(true);
	} else if (outside(other)) {
		return makeCollision<PointsColl>(false);
	} else {
		Coord ans1, ans2;
		auto x0 = center.x, y0 = center.y, x1 = other.center.x, y1 = other.center.y, r0 = radius, r1 = other.radius;
		auto u1 = x1 - x0, v1 = y1 - y0;
		auto C = (r1 * r1 - radius * radius - u1 * u1 - v1 * v1) / 2;
		auto a = u1 * u1 + v1 * v1, b = 2 * v1 * C, c = C * C - r0 * r0 * u1 * u1;
		auto D = b * b - 4 * a * c;
		auto f = [u1, v1, r1](gm::coord u, gm::coord v) {
			return (u - u1) * (u - u1) + (v - v1) * (v - v1) - r1 * r1;
		};
		if (D < 0.) {
			return makeCollision<PointsColl>(false);
		} else if (D == 0) {
			auto v = -b / (2 * a), u = sqrt(r0 * r0 - v * v);
			if (abs(f(u, v)) > 0.001) {
				u = -u;
			}
			ans1.x = u + x0;
			ans1.y = v + y0;
			return makeCollision<PointsColl>(std::initializer_list{ ans1 });
		} else {
			auto v_1 = (-b + sqrt(D)) / (2 * a), u_1 = sqrt(r0 * r0 - v_1 * v_1);
			if (abs(f(u_1, v_1)) > 0.001) {
				u_1 = -u_1;
			}
			ans1.x = u_1 + x0;
			ans1.y = v_1 + y0;

			auto v_2 = (-b - sqrt(D)) / (2 * a), u_2 = sqrt(r0 * r0 - v_2 * v_2);
			if (abs(f(u_2, v_2)) > 0.001) {
				u_2 = -u_2;
			}
			ans2.x = u_2 + x0;
			ans2.y = v_2 + y0;

			return makeCollision<PointsColl>(std::initializer_list{ ans1, ans2 });
		}
	}
}

Collision gm::Circle::collides(const Rectangle& rect) const { // V
	if (inside(rect) || rect.inside(*this)) {
		return makeCollision<PointsColl>(true);
	} else if (outside(rect)) {
		return makeCollision<PointsColl>(false);
	} else {
		std::vector<Coord> ps;
		ps.reserve(8);
		auto f = [&](const Coord& p0, const Coord& p1) {
			auto res = collides(Sect(p0, p1));
			auto pc2 = dynamic_cast<PointsColl2*>(*res);
			if (pc2->getCount() >= 1) {
				ps.push_back(pc2->getFirst());
			}
			if (pc2->getCount() == 2) {
				ps.push_back(pc2->getSecond());
			}
		};
		f(rect.getLeftTop(), { std::nextafter(rect.getRight(), rect.getLeft()), rect.getTop() });
		f(rect.getRightTop(), { rect.getRight(), std::nextafter(rect.getBottom(), rect.getTop())});
		f(rect.getRightBottom(), { std::nextafter(rect.getLeft(), rect.getRight()), rect.getBottom()});
		f(rect.getLeftBottom(), {rect.getLeft(), std::nextafter(rect.getTop(), rect.getBottom())});
		return makeCollision<PointsColl>(ps);
	}
}

bool gm::Circle::contains(const Coord& point) const { // V
	return center / point <= radius;
}
