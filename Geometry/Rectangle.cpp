#include "Rectangle.h"

gm::Rectangle::Rectangle() : leftTop(0, 0), size(1, 1) {
}

gm::Rectangle::Rectangle(const Coord2D& leftTop, const Size2D& size) : leftTop(leftTop), size(size) {
}

gm::Rectangle::Rectangle(coord left, coord top, real width, real heigth) : leftTop(left, top), size(width, heigth)
{
}

gm::Rectangle gm::Rectangle::LTRB(const Coord2D& leftTop, const Coord2D& rightBottom) {
	return Rectangle(leftTop, rightBottom - leftTop);
}

bool gm::Rectangle::operator==(const Rectangle& other) const {
	return leftTop == other.leftTop && size == other.size;
}

bool gm::Rectangle::operator!=(const Rectangle& other) const {
	return !(*this == other);
}

void gm::Rectangle::move(const Vector2D& v) {
	leftTop += v;
}

const gm::Coord2D gm::Rectangle::getPosition() const {
	return leftTop;
}

gm::Coord2D gm::Rectangle::getCenter() const {
	return leftTop + size / 2;
}

void gm::Rectangle::setCenter(const Coord2D& center) {
	leftTop = center - size / 2;
}

void gm::Rectangle::scale(const Vector2D& scale) {
	size.x *= scale.x;
	size.y *= scale.y;
}

gm::real gm::Rectangle::getXScale() const {
	return 1;
}

gm::real gm::Rectangle::getYScale() const {
	return 1;
}

const gm::Size2D gm::Rectangle::getSize()const {
	return size;
}

void gm::Rectangle::setSize(const gm::Size2D& newSize) {
	size = newSize;
}

const gm::Coord2D gm::Rectangle::getLeftTop() const {
	return leftTop;
}

const gm::Coord2D gm::Rectangle::getRightTop() const {
	return leftTop.addX(size.x);
}

const gm::Coord2D gm::Rectangle::getLeftBottom() const {
	return leftTop.addY(size.y);
}

const gm::Coord2D gm::Rectangle::getRightBottom() const {
	return leftTop + size;
}

gm::coord gm::Rectangle::getLeft() const {
	return leftTop.x;
}

gm::coord gm::Rectangle::getRight() const {
	return leftTop.x + size.x;
}

gm::coord gm::Rectangle::getTop() const {
	return leftTop.y;
}

gm::coord gm::Rectangle::getBottom() const {
	return leftTop.y + size.y;
}

std::optional<gm::Rectangle> gm::Rectangle::intersect(const Rectangle& o) const{
	if (getLeft() > o.getRight() || getRight() < o.getLeft() || getTop() > o.getBottom() || getBottom() < o.getTop()) {
		return std::nullopt;
	}
	return Rectangle::LTRB(
		{ std::max(getLeft(), o.getLeft()), std::max(getTop(), o.getTop()) },
		{ std::min(getRight(), o.getRight()), std::min(getBottom(), o.getBottom()) }
	);
}

bool gm::Rectangle::inside(const Rectangle& other) const {
	return *this == intersect(other);
}

bool gm::Rectangle::contain(const Rectangle& other) const {
	return other == intersect(other);
}
