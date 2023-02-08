#include "Rectangle.h"
#include "Circle.h"
using namespace gm;

gm::Rectangle::Rectangle() : leftTop(0, 0), size(1, 1) {}

gm::Rectangle::Rectangle(const Coord& leftTop, const Size& size) : leftTop(leftTop), size(size) {}

gm::Rectangle::Rectangle(coord left, coord top, real width, real heigth) : leftTop(left, top), size(width, heigth) {}

gm::Rectangle gm::Rectangle::LTRB(const Coord& leftTop, const Coord& rightBottom) {
	return Rectangle(leftTop, rightBottom - leftTop);
}

bool gm::Rectangle::operator==(const Rectangle& other) const {
	return leftTop == other.leftTop && size == other.size;
}

bool gm::Rectangle::operator!=(const Rectangle& other) const {
	return !(*this == other);
}

void gm::Rectangle::move(const Vector& v) {
	leftTop += v;
}

const gm::Coord gm::Rectangle::getPosition() const {
	return leftTop;
}

const gm::Size gm::Rectangle::getSize()const {
	return size;
}

void gm::Rectangle::setSize(const gm::Size& newSize) {
	size = newSize;
}

const gm::Vector gm::Rectangle::getScale() const {
	return { 1,1 };
}

void gm::Rectangle::scale(const gm::Vector& scale) {
	size.x *= scale.x;
	size.y *= scale.y;
}

bool gm::Rectangle::contains(const Coord& point) const {
	return getLeft() <= point.x && getRight() >= point.x && getTop() <= point.y && getBottom() >= point.y;
}

const gm::Rectangle gm::Rectangle::getBounds() const {
	return *this;
}

const Sect gm::Rectangle::getLeftSect() const {
	return Sect(leftTop, leftTop.addY(size.y));
}

const Sect gm::Rectangle::getTopSect() const {
	return Sect(leftTop, leftTop.addX(size.x));
}

const Sect gm::Rectangle::getRightSect() const {
	return Sect(leftTop.addX(size.x), leftTop + size);
}

const Sect gm::Rectangle::getBottomSect() const {
	return Sect(leftTop.addY(size.y), leftTop + size);
}

// inside
bool gm::Rectangle::inside(const Line& other) const { // V
	return false;
}

bool gm::Rectangle::inside(const Sect& other) const { // V
	return false;
}

bool gm::Rectangle::inside(const Circle& other) const { // V
	return
		other.contains(getLeftTop()) &&
		other.contains(getRightTop()) &&
		other.contains(getLeftBottom()) &&
		other.contains(getRightBottom());
}

bool gm::Rectangle::inside(const Rectangle& other) const { // V
	return getLeft() >= other.getLeft() && getRight() <= other.getRight() && getTop() >= other.getTop() && getBottom() >= other.getBottom();
}

// outside
bool gm::Rectangle::outside(const Line& other) const { // V
	return 
		!getTopSect().collides(other) && 
		!getLeftSect().collides(other) && 
		!getRightSect().collides(other) && 
		!getBottomSect().collides(other);
}

bool gm::Rectangle::outside(const Sect& other) const { // V
	return !contains(other.p0) && !contains(other.p1);
}

bool gm::Rectangle::outside(const Circle& other) const { // V
	return other.outside(*this);
}

bool gm::Rectangle::outside(const Rectangle& o) const { // V
	return getLeft() > o.getRight() || getRight() < o.getLeft() || getTop() > o.getBottom() || getBottom() < o.getTop();
}

// collides
Collision gm::Rectangle::collides(const Line& other) const { // V
	auto 
		lc = getLeftSect().collides(other).getPoints(),
		tc = getTopSect().collides(other).getPoints(),
		rc = getRightSect().collides(other).getPoints(),
		bc = getBottomSect().collides(other).getPoints();
	PointsArray res;
	res.reserve(lc.size() + tc.size() + rc.size() + bc.size());
	auto it = res.begin();
	it = res.insert(it, lc.begin(), lc.end());
	it = res.insert(it, tc.begin(), tc.end());
	it = res.insert(it, rc.begin(), rc.end());
	it = res.insert(it, bc.begin(), bc.end());
	return makeCollision<PointsColl>(std::move(res));
}

Collision gm::Rectangle::collides(const Sect& other) const { // V
	auto
		lc = getLeftSect().collides(other).getPoints(),
		tc = getTopSect().collides(other).getPoints(),
		rc = getRightSect().collides(other).getPoints(),
		bc = getBottomSect().collides(other).getPoints();
	PointsArray res;
	res.reserve(lc.size() + tc.size() + rc.size() + bc.size());
	auto it = res.begin();
	it = res.insert(it, lc.begin(), lc.end());
	it = res.insert(it, tc.begin(), tc.end());
	it = res.insert(it, rc.begin(), rc.end());
	it = res.insert(it, bc.begin(), bc.end());
	return makeCollision<PointsColl>(std::move(res));
}

Collision gm::Rectangle::collides(const Circle& other) const { // V
	return other.collides(*this);
}

Collision gm::Rectangle::collides(const Rectangle& o) const { // V
	if (outside(o)) {
		return makeCollision<RectangleColl>(false);
	}
	auto res = Rectangle::LTRB(
		{ std::max(getLeft(), o.getLeft()), std::max(getTop(), o.getTop()) },
		{ std::min(getRight(), o.getRight()), std::min(getBottom(), o.getBottom()) }
	);
	std::bitset<4> corners;
	auto lt = res.getLeftTop(), rt = res.getRightTop(), lb = res.getLeftBottom(), rb = res.getRightBottom();
	if (lt.x == getLeft() && lt.y == o.getTop() || lt.x == o.getLeft() && lt.y == getTop()) {
		corners[0] = 1;
	}
	if (rt.x == getRight() && rt.y == o.getTop() || rt.x == o.getRight() && rt.y == getTop()) {
		corners[1] = 1;
	}
	if (lb.x == getLeft() && lb.y == o.getBottom() || lb.x == o.getLeft() && lb.y == getBottom()) {
		corners[2] = 1;
	}
	if (rb.x == getRight() && rb.y == o.getBottom() || rb.x == o.getRight() && rb.y == getBottom()) {
		corners[3] = 1;
	}
	return makeCollision<RectangleColl>(res, corners);
}


gm::RectangleColl::RectangleColl(bool coll) :collide(coll) {}

gm::RectangleColl::RectangleColl(const Rectangle& rect, int first, int second) :
	coll(rect), collide(true) {
	corners[first] = 1;
	corners[second] = 1;
}

gm::RectangleColl::RectangleColl(const Rectangle& rect, std::bitset<4> corners) :
	coll(rect), corners(corners), collide(true) {}

gm::RectangleColl::operator bool() const { return collide; }

PointsArray gm::RectangleColl::getPoints() const {
	PointsArray par;
	if (islt()) {
		par.push_back(coll.getLeftTop());
	}
	if (isrt()) {
		par.push_back(coll.getRightTop());
	}
	if (islb()) {
		par.push_back(coll.getLeftBottom());
	}
	if (isrb()) {
		par.push_back(coll.getRightBottom());
	}
	return par;
}

const Rectangle& gm::RectangleColl::getRect() const {
	return coll;
}

const Coord gm::RectangleColl::getFirst() const {
	return
		corners[0] ? coll.getLeftTop() :
		corners[1] ? coll.getRightTop() :
		corners[2] ? coll.getLeftBottom() :
		NV;
}

const Coord gm::RectangleColl::getSecond() const {
	return
		corners[3] ? coll.getRightBottom() :
		corners[2] ? coll.getLeftBottom() :
		corners[1] ? coll.getRightTop() :
		NV;
}

bool gm::RectangleColl::islt() const {
	return corners[0];
}

bool gm::RectangleColl::isrt() const {
	return corners[1];
}

bool gm::RectangleColl::islb() const {
	return corners[2];
}

bool gm::RectangleColl::isrb() const {
	return corners[3];
}
