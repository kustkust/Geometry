#pragma once
#include <cmath>
#include <ios>

namespace gm {
	constexpr auto PI = 3.141592653589793;
	constexpr auto PI_1_2 = PI / 2;
	constexpr auto PI_3_2 = PI * 3 / 2;
	constexpr auto PI2 = PI * 2;

	constexpr auto GtoR = PI / 180;
	constexpr auto RtoG = 180 / PI;

	using uint = unsigned int;

	using real = double;
	using coord = real;
	using lenght = coord;
	using speed = coord;

	using angle = double;
	enum class Ang {
		A90,
		A180,
	};

	class Vector;
	using Coord = Vector;
	using Size = Vector;

	class IMoveable;
	class IScaleable;
	class IRotateable;

	class Shape;
	class Line;
	class Sect;
	class Circle;
	class Rectangle;

	class Matrix2;
	class Matrix3;

	bool OE(real x, real y = 0, real e = 0.01);
	int sign(real i);
	const real inversSquareRoot(real len);

	extern std::streamsize precision;
}