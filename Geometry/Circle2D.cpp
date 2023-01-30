#include "Circle2D.h"
using namespace gm;
const Vector2D Circle2D::getV()const {
	return Vector2D(c.x, c.y + r);
}
Circle2D::Circle2D(Coord2D c_, coord r_) {
	c = c_;
	r = r_;
}
Circle2D::Circle2D() :Circle2D(NV, 1) {

}
const short int Circle2D::ins(const Line2D& l, Coord2D& ans1, Coord2D& ans2)const {
	coord h = l | c;
	if (OE(abs(h), r)) {
		ans1 = c - l.n.relen(h);
		ans2 = ans1;
		return 1;
	} else if (abs(h) > r) {
		ans1 = NV;
		ans2 = NV;
		return 0;
	} else if (abs(h) < r) {
		const Coord2D ans = c - l.n(h);
		const coord d = sqrt(r * r - h * h);
		ans1 = ans + (l.n >> Ang::A90).relen(d);
		ans2 = ans + (l.n << Ang::A90).relen(d);
		return 2;
	}
	return -1;
}
const bool Circle2D::isins(const Line2D& l)const {
	coord h = l | c;
	return OE(abs(h), r) || abs(h) < r;
}
const int gm::Circle2D::ins(const Circle2D& other, Coord2D& ans1, Coord2D& ans2) const {
	auto x0 = c.x, y0 = c.y, x1 = other.c.x, y1 = other.c.y, r0 = r, r1 = other.r;
	auto u1 = x1 - x0, v1 = y1 - y0;
	auto C = (r1 * r1 - r * r - u1 * u1 - v1 * v1) / 2;
	auto a = u1 * u1 + v1 * v1, b = 2 * v1 * C, c = C * C - r0 * r0 * u1 * u1;
	auto D = b * b - 4 * a * c;
	auto f = [u1, v1, r1](gm::coord u, gm::coord v) {
		return (u - u1) * (u - u1) + (v - v1) * (v - v1) - r1 * r1;
	};
	if (D < 0.) {
		return 0;
	} else if (D == 0) {
		auto v = -b / (2 * a), u = sqrt(r0 * r0 - v * v);
		if (abs(f(u, v)) > 0.001) {
			u = -u;
		}
		ans1.x = u + x0;
		ans1.y = v + y0;
		return 1;
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

		return 2;
	}
}
void Circle2D::resize(const Coord2D& p) {
	r = !(p - c);
}
