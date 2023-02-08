#include "Vector.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
using namespace gm;


bool gm::IShape::inside(const IShape& other) const {
    return inside(&other);
}

bool gm::IShape::inside(const IShape* p) const {
    if (auto line = dynamic_cast<const Line*>(p)) {
        return inside(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return inside(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return inside(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return inside(*circle);
    }
    return false;
}

bool gm::IShape::outside(const IShape& other) const {
    return outside(&other);
}

bool gm::IShape::outside(const IShape* p) const {
    if (auto line = dynamic_cast<const Line*>(p)) {
        return outside(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return outside(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return outside(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return outside(*circle);
    }
    return false;
}

Collision gm::IShape::collides(const IShape& other) const {
    return collides(other);
}

Collision gm::IShape::collides(const IShape* p) const {
    if (auto line = dynamic_cast<const Line*>(p)) {
        return collides(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return collides(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return collides(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return collides(*circle);
    }
    return Collision();
}

bool gm::IShape::fastCollides(const IShape& other) const {
    return fastCollides(other);
}

bool gm::IShape::fastCollides(const IShape* other) const {
    return !outside(other);
}



Shape::Shape(Shape&& other) noexcept {
    if (this != &other) {
        shape = other.shape;
    }
}

Shape& Shape::operator=(Shape&& other) noexcept {
    if (this != &other) {
        shape = other.shape;
    }
    return *this;
}

Shape::Shape(IShape* sptr) : shape(sptr) {

}

// Scale
void gm::Shape::scale(const Vector& scale) {
    shape->scale(scale);
}

const Vector gm::Shape::getScale() const {
    return shape->getScale();
}

// Move
void gm::Shape::move(const Vector& v) {
    shape->move(v);
}

const Coord gm::Shape::getPosition() const {
    return shape->getPosition();
}

// Size
const Size gm::Shape::getSize() const {
    return shape->getSize();
}

void gm::Shape::setSize(const gm::Size& newSize) {
    shape->setSize(newSize);
}

// inside
bool gm::Shape::inside(const Shape& other) const {
    auto p = other.get();
    if (auto line = dynamic_cast<const Line*>(p)) {
        return shape->inside(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return shape->inside(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return shape->inside(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return shape->inside(*circle);
    }
    return false;
}

bool gm::Shape::inside(const Line& other) const {
    return shape->inside(other);
}

bool gm::Shape::inside(const Sect& other) const {
    return shape->inside(other);
}

bool gm::Shape::inside(const Rectangle& other) const {
    return shape->inside(other);
}

bool gm::Shape::inside(const Circle& other) const {
    return shape->inside(other);
}

// outside
bool gm::Shape::outside(const Shape& other) const {
    auto p = other.get(); 
    if (auto line = dynamic_cast<const Line*>(p)) {
        return shape->outside(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return shape->outside(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return shape->outside(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return shape->outside(*circle);
    }
    return false;
}

bool gm::Shape::outside(const Line& other) const {
    return shape->outside(other);
}

bool gm::Shape::outside(const Sect& other) const {
    return shape->outside(other);
}

bool gm::Shape::outside(const Circle& other) const {
    return shape->outside(other);
}

bool gm::Shape::outside(const Rectangle& other) const {
    return shape->outside(other);
}

// collides
Collision gm::Shape::collides(const Shape& other) const {
    auto p = other.get();
    if (auto line = dynamic_cast<const Line*>(p)) {
        return shape->collides(*line);
    } else if (auto sect = dynamic_cast<const Sect*>(p)) {
        return shape->collides(*sect);
    } else if (auto rect = dynamic_cast<const Rectangle*>(p)) {
        return shape->collides(*rect);
    } else if (auto circle = dynamic_cast<const Circle*>(p)) {
        return shape->collides(*circle);
    }
    return Collision();
}

Collision gm::Shape::collides(const Line& other) const {
    return shape->collides(other);
}

Collision gm::Shape::collides(const Sect& other) const {
    return shape->collides(other);
}

Collision gm::Shape::collides(const Circle& other) const {
    return shape->collides(other);
}

Collision gm::Shape::collides(const Rectangle& other) const {
    return shape->collides(other);
}

// contains
bool gm::Shape::contains(const Shape& other) const {
    return other.inside(*this);
}

bool gm::Shape::contains(const Coord& point) const {
    return shape->contains(point);
}
