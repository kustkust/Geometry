#include <cmath>
#include <iostream>
#include "Line2D.h"
#define A n.x
#define B n.y
using namespace gm;
void Line2D::calc(const Vector2D& t0, const Vector2D& t1) {
	n.x = (t0.y - t1.y);
	n.y = -(t0.x - t1.x);
	C = (t1.y * t0.x - t0.y * t1.x);
}
Line2D::Line2D(const Vector2D& t0, const Vector2D& t1) {
	n.x = (t0.y - t1.y);
	n.y = -(t0.x - t1.x);
	C = (t1.y * t0.x - t0.y * t1.x);
}
Line2D::Line2D(const Vector2D& n_, const coord& C_) {
	n = n_;
	C = C_;
}
Line2D::Line2D(const Vector2D& t0, const Vector2D& v, int) :Line2D(t0, t0 + v) {}
Line2D::Line2D(const coord x0, const  coord y0, const coord x1, const coord y1) :
	Line2D(Vector2D(x0, y0), Vector2D(x1, y1)) {}
Line2D::Line2D(const Line2D& l) {
	n = l.n;
	C = l.C;
}
const Line2D gm::Line2D::pointNormal(const Coord2D& p, const Vector2D& n_) {
	Line2D tmp;
	tmp.n = n_;
	tmp.C = -(n_ * p);
	return tmp;
}
const gm::lenght gm::Line2D::operator/(const gm::Line2D& l) const {
	return abs(l.C / !l.n - C / !n);
}
void gm::Line2D::normalize() {
	auto k = !n;
	n /= k;
	C /= k;
}
const Coord2D Line2D::operator%(const Coord2D p) const {//ÂÎÇÂÐÀÙÀÅÒ ÒÎ×ÊÓ ÑÈÌÌÅÒÐÈ×ÍÓÞ t ÎÒÍÎÑÒÈÒÅËÜÍÎ ÄÀÍÍÎÉ ÏÐßÌÎÉ 
	coord k = (A * p.x + B * p.y + C) / (A * A + B * B);
	return Coord2D(p.x - 2 * A * k, p.y - 2 * B * k);
}
const coord Line2D::operator|(const Coord2D& t) const {//ÎÒÊËÎÍÅÍÈÅ ÒÎ×ÊÈ ÎÒ ÏÐßÌÎÉ
	return (A * t.x + B * t.y + C) / sqrt(A * A + B * B);
}
const coord Line2D::operator/(const Coord2D& t) const {//ÎÒÊËÎÍÅÍÈÅ ÒÎ×ÊÈ ÎÒ ÏÐßÌÎÉ
	return abs((*this) | t);
}
bool Line2D::operator||(const Line2D& l) const {
	return OE(A * l.B, l.A * B, 0.001);
}
const Vector2D Line2D::operator*(const Line2D l) const {
	auto m0 = A * l.B - l.A * B;
	if (gm::OE(m0, 0., 0.00000001)) {
		throw "operator* : (*this || l)";
	}
	return {
		(-C * l.B - (-l.C * B)) / m0,
		(-l.C * A - (-C * l.A)) / m0 };
}
const Line2D Line2D::operator*(const coord k) const {
	Line2D l(*this);
	l.n *= k;
	l.C *= k;
	return l;
}
Line2D& Line2D::operator*= (const coord l) {
	n *= l;
	C *= l;
	return (*this);
}
bool Line2D::nei(const Vector2D& t, const coord& e) const {
	return e >= abs((*this) | t);
}
std::ostream& operator<<(std::ostream& co, const Line2D& l) {
	co << "(" << (l.n) << " " << l.C << ")";
	return co;
}
const coord Line2D::ang_b(const Line2D& l)const {
	return n ^ l.n;
}
const coord gm::Line2D::operator^(const Line2D& l) const {
	return ang_b(l);
}
const Coord2D Line2D::projection(const Coord2D p)const {
	lenght k = (A * p.x + B * p.y + C) / (A * A + B * B);
	return Coord2D(p.x - A * k, p.y - B * k);
}
const Line2D Line2D::relen_n(lenght k)const {
	Line2D l(*this);
	if (k != 0) {
		k /= !n;
		l.n *= k;
		l.C *= k;
	}
	return l;
}
Line2D& Line2D::srelen_n(lenght k) {
	if (k != 0) {
		k /= !n;
		n *= k;
		C *= k;
	}
	return (*this);
}

Vector2D gm::Line2D::getDir() const {
	return n << gm::Ang::A90;
}
