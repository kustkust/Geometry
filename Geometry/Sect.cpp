#include "Sect.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
using namespace gm;

gm::Sect::Sect() :
	p0(gm::VI), p1(gm::VJ) {}
Sect::Sect(const Coord& p0_, const Coord& p1_) : p0(p0_), p1(p1_) {

}
Sect::Sect(coord x0, coord y0, coord x1, coord y1) : p0(x0, y0), p1(x1, y1) {

}
const Line gm::Sect::getLine() const {
	return Line(p0, p1);
}
bool gm::Sect::intersection(const Sect& s, gm::Coord& p) const {
	Line l0(p0, p1);
	Line l1(s.p0, s.p1);
	if (!(l0 || l1)) {
		p = l0 * l1;
		return between(p) && s.between(p);
	} else {
		auto d0 = lenght(s.p0);
		auto d1 = lenght(s.p1);
		if (d0 < d1) {
			if (OE(d0)) {
				p = s.p0;
				return true;
			}
		} else {
			if (OE(d1)) {
				p = s.p1;
				return true;
			}
		}
	}
	return false;
}
gm::lenght Sect::deviation(const gm::Coord& p) const {
	if ((p - p0) * (p1 - p0) < 0) {
		return p / p0;
	} else if ((p - p1) * (p0 - p1) < 0) {
		return p / p1;
	}
	auto p_ = Line(p0, p1) / p;
	return p_;
}
gm::lenght Sect::lenght(const gm::Coord& p) const {
	auto tmp = deviation(p);
	return tmp * sign(tmp);
}
void gm::Sect::scale(const Vector& scale) {}
const Vector gm::Sect::getScale() const {
	return Vector();
}
void gm::Sect::move(const Vector& v) {}
const Coord gm::Sect::getPosition() const {
	return getCenter();
}
const Coord gm::Sect::getCenter() const {
	return (p0 + p1) / 2;
}
const Coord gm::Sect::getLeftTop() const {
	return Coord(std::min(p0.x, p1.x), std::min(p0.y, p1.y));
}
const Coord gm::Sect::getRightBottom() const {
	return Coord(std::max(p0.x, p1.x), std::max(p0.y, p1.y));
}
const Size gm::Sect::getSize() const {
	return getRightBottom() - getLeftTop();
}
void gm::Sect::setSize(const gm::Size& newSize) {
	bool swaped = p0.x > p1.x;
	if (swaped) {
		std::swap(p0, p1);
	}
	auto c = getCenter();
	if (p0.y < p1.y) {
		p0 = c - newSize / 2;
		p1 = c + newSize / 2;
	} else {
		p0 = c - newSize.invY() / 2;
		p1 = c + newSize.invY() / 2;
	}
	if (swaped) {
		std::swap(p0, p1);
	}
}

// inside
bool gm::Sect::inside(const Line& other) const { // V
	return other.contains(p0) && other.contains(p1);
}
bool gm::Sect::inside(const Sect& other) const { // V
	return other.contains(p0) && other.contains(p1);
}
bool gm::Sect::inside(const Circle& other) const { // V
	return other.contains(p0) && other.contains(p1);
}
bool gm::Sect::inside(const Rectangle& other) const { // V
	return other.contains(p0) && other.contains(p1);
}

// outside
bool gm::Sect::outside(const Line& other) const { // V
	return (other / p1)*(other / p0) > 0;
}
bool gm::Sect::outside(const Sect& s) const { // V
	auto v0 = p1 - p0;
	auto v1 = s.p1 - s.p0;
	return
		(v0 % (s.p0 - p0)) * (v0 % (s.p1 - p0)) <= 0. &&
		(v1 % (p0 - s.p0)) * (v1 % (p1 - s.p0)) <= 0.;
}
bool gm::Sect::outside(const Circle& other) const { // V
	return other.outside(*this);
}
bool gm::Sect::outside(const Rectangle& other) const { // V
	return other.outside(*this);
}

// collides
Collision gm::Sect::collides(const Line& other) const { // V
	auto col = getLine().collides(other);
	if (col && between(col.getPoints()[0])) {
		return col;
	}
	return makeCollision<SimpleCollision>();
}
Collision gm::Sect::collides(const Sect& s) const { // V
	Line l0(p0, p1);
	Line l1(s.p0, s.p1);
	if (!(l0 || l1)) {
		auto p = l0 * l1;
		if (between(p) && s.between(p)) {
			return makeCollision<SimpleCollision>(p);
		}
	} else {
		auto d0 = lenght(s.p0);
		auto d1 = lenght(s.p1);
		if (d0 < d1) {
			if (OE(d0)) {
				return makeCollision<SimpleCollision>(s.p0);
			}
		} else {
			if (OE(d1)) {
				return makeCollision<SimpleCollision>(s.p1);
			}
		}
	}
	return makeCollision<SimpleCollision>();
}
Collision gm::Sect::collides(const Circle& other) const { // V
	return other.collides(*this);
}
Collision gm::Sect::collides(const Rectangle& other) const { // V
	return other.collides(*this);
}

bool gm::Sect::contains(const Coord& p) const {
	auto v = p1 - p0;
	return v * (p - p0) > 0 && v * (p - p1) < 0;
}
std::vector<Sect> Sect::getSects(const std::vector<Coord>& points) {
	std::vector<Sect> sects;
	sects.reserve(points.size());
	for (unsigned i = 0; i < points.size() - 1; i++) {
		sects.push_back(Sect(points[i], points[i + 1]));
	}
	sects.push_back(Sect(points.back(), points.front()));
	return sects;
}

const bool gm::Sect::between(const Coord p) const {
	return ((p - p0) * (p1 - p0) >= 0) && ((p - p1) * (p0 - p1) >= 0);
}
