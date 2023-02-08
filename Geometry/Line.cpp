#include <cmath>
#include <iostream>
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"

#define A n.x
#define B n.y
using namespace gm;

void Line::calc(const Vector& t0, const Vector& t1) {
	n.x = (t0.y - t1.y);
	n.y = -(t0.x - t1.x);
	C = (t1.y * t0.x - t0.y * t1.x);
}
Line::Line(const Vector& t0, const Vector& t1) {
	n.x = (t0.y - t1.y);
	n.y = -(t0.x - t1.x);
	C = (t1.y * t0.x - t0.y * t1.x);
}
Line::Line(const Vector& n_, const coord& C_) {
	n = n_;
	C = C_;
}
Line::Line(const coord x0, const  coord y0, const coord x1, const coord y1) :
	Line(Vector(x0, y0), Vector(x1, y1)) {}
Line::Line(const Line& l) {
	n = l.n;
	C = l.C;
}
const Line Line::pointNormal(const Coord& p, const Vector& n_) {
	Line tmp;
	tmp.n = n_;
	tmp.C = -(n_ * p);
	return tmp;
}
const lenght Line::operator/(const Line& l) const {
	return abs(l.C / !l.n - C / !n);
}
void Line::normalize() {
	auto k = !n;
	n /= k;
	C /= k;
}
bool gm::Line::operator==(const Line& other) const {
	return (n % other.n) < 0.00001 && OE(C / !n, other.C / !n);
}
const Coord Line::operator%(const Coord p) const {//ÂÎÇÂÐÀÙÀÅÒ ÒÎ×ÊÓ ÑÈÌÌÅÒÐÈ×ÍÓÞ t ÎÒÍÎÑÒÈÒÅËÜÍÎ ÄÀÍÍÎÉ ÏÐßÌÎÉ 
	coord k = (A * p.x + B * p.y + C) / (A * A + B * B);
	return Coord(p.x - 2 * A * k, p.y - 2 * B * k);
}
const coord Line::operator/(const Coord& t) const {//ÎÒÊËÎÍÅÍÈÅ ÒÎ×ÊÈ ÎÒ ÏÐßÌÎÉ
	return (A * t.x + B * t.y + C) / sqrt(A * A + B * B);
}
bool Line::operator||(const Line& l) const {
	return OE(A * l.B, l.A * B, 0.001);
}
const Vector Line::operator*(const Line l) const {
	auto m0 = A * l.B - l.A * B;
	if (OE(m0, 0., 0.00000001)) {
		throw "operator* : (*this || l)";
	}
	return {
		(-C * l.B - (-l.C * B)) / m0,
		(-l.C * A - (-C * l.A)) / m0 };
}
const Line Line::operator*(const coord k) const {
	Line l(*this);
	l.n *= k;
	l.C *= k;
	return l;
}
Line& Line::operator*= (const coord l) {
	n *= l;
	C *= l;
	return (*this);
}
std::ostream& operator<<(std::ostream& co, const Line& l) {
	co << "(" << (l.n) << " " << l.C << ")";
	return co;
}
const coord Line::ang_b(const Line& l)const {
	return n ^ l.n;
}
const coord Line::operator^(const Line& l) const {
	return ang_b(l);
}
const Coord Line::projection(const Coord p)const {
	lenght k = (A * p.x + B * p.y + C) / (A * A + B * B);
	return Coord(p.x - A * k, p.y - B * k);
}
const Line Line::relen_n(lenght k)const {
	Line l(*this);
	if (k != 0) {
		k /= !n;
		l.n *= k;
		l.C *= k;
	}
	return l;
}
Line& Line::srelen_n(lenght k) {
	if (k != 0) {
		k /= !n;
		n *= k;
		C *= k;
	}
	return (*this);
}

Vector Line::getDir() const {
	return n << Ang::A90;
}

void gm::Line::scale(const Vector& scale) {}

const Vector gm::Line::getScale() const {
	return VXY;
}

void gm::Line::move(const Vector& v) {
	C = -((getPosition() + v) * n);
}

const Coord gm::Line::getPosition() const {
	Coord point;
	if (n.x != 0) {
		point.x = -C / n.x;
	} else {
		point.y = -C / n.y;
	}
	return point;
}

const Size gm::Line::getSize() const {
	return VXY;
}

void gm::Line::setSize(const gm::Size& newSize) {}

bool gm::Line::inside(const Line& other) const { // V
	return operator==(other);
}

bool gm::Line::inside(const Sect& other) const { // V
	return false;
}

bool gm::Line::inside(const Circle& other) const { // V
	return false;
}

bool gm::Line::inside(const Rectangle& other) const { // V
	return false;
}

bool gm::Line::outside(const Line& other) const { // V
	return *this || other;
}

bool gm::Line::outside(const Sect& other) const { // V
	return other.outside(*this);
}

bool gm::Line::outside(const Circle& other) const { // V
	return other.outside(*this);
}

bool gm::Line::outside(const Rectangle& other) const { // V
	return other.outside(*this);
}

Collision gm::Line::collides(const Line& other) const { // V
	if (*this || other) {
		return makeCollision<SimpleCollision>();
	}
	return makeCollision<SimpleCollision>(operator*(other));
}

Collision gm::Line::collides(const Sect& other) const { // V
	return other.collides(*this);
}

Collision gm::Line::collides(const Circle& other) const { // V
	return other.collides(*this);
}

Collision gm::Line::collides(const Rectangle& other) const { // V
	return other.collides(*this);
}

bool gm::Line::contains(const Coord& point) const {
	return std::abs(*this / point) < 0.00000001;
}
