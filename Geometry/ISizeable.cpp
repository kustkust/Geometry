#include "Vector.h"
#include "ISizeable.h"
#include "Rectangle.h"

const gm::Coord gm::ISizeable::getCenter() const {
	return getLeftTop() + getSize() / 2;
}

void gm::ISizeable::setCenter(const Coord& center) {
	setLeftTop(center - getSize() / 2);
}

const gm::Coord gm::ISizeable::getLeftTop() const {
	return getPosition();
}

const gm::Coord gm::ISizeable::getRightTop() const {
	return getLeftTop().addX(getSize().x);
}

const gm::Coord gm::ISizeable::getLeftBottom() const {
	return getLeftTop().addY(getSize().y);
}

const gm::Coord gm::ISizeable::getRightBottom() const {
	return getLeftTop() + getSize();
}

void gm::ISizeable::setLeftTop(const Coord& center) {
	setPosition(center);
}

void gm::ISizeable::setRightTop(const Coord& center) {
	setLeftTop(center.addX(getWidth()));
}

void gm::ISizeable::setLeftBottom(const Coord& center) {
	setLeftTop(center.addY(getHeight()));
}

void gm::ISizeable::setRightBottom(const Coord& center) {
	setLeftTop(center + getSize());
}


gm::coord gm::ISizeable::getLeft() const {
	return getLeftTop().x;
}

gm::coord gm::ISizeable::getRight() const {
	return getLeftTop().x + getSize().x;
}

gm::coord gm::ISizeable::getTop() const {
	return getLeftTop().y;
}

gm::coord gm::ISizeable::getBottom() const {
	return getLeftTop().y + getSize().y;
}

const gm::Coord gm::ISizeable::getLeftCenter() const {
	return getLeftTop().addY(getSize().y/2);
}

const gm::Coord gm::ISizeable::getRightCenter() const {
	return getRightTop().addY(getSize().y / 2);
}

const gm::Coord gm::ISizeable::getTopCenter() const {
	return getLeftTop().addX(getSize().x / 2);
}

const gm::Coord gm::ISizeable::getBottomCenter() const {
	return getLeftBottom().addX(getSize().x / 2);
}

void gm::ISizeable::setSize(gm::lenght newSize) {
	setSize({ newSize, newSize });
}

gm::lenght gm::ISizeable::getWidth() const {
	return getSize().x;
}

gm::lenght gm::ISizeable::getHeight() const {
	return getSize().y;
}

const gm::Rectangle gm::ISizeable::getBounds() const {
	return {getLeftTop(), getSize()};
}
