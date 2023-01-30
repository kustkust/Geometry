#pragma once
#include <cmath>

namespace gm {
	constexpr auto PI = 3.141592653589793;
	constexpr auto PI_1_2 = PI / 2;
	constexpr auto PI_3_2 = PI * 3 / 2;
	constexpr auto PI2 = PI * 2;

	constexpr auto GtoR = PI / 180;
	constexpr auto RtoG = 180 / PI;

	using uint = unsigned int;

	using real = double;//при изменении не забыть про приведение типов
	using coord = real;
	using lenght = coord;
	using speed = coord;

	using angle = double;
	enum class Ang {
		A90,
		A180,
	};

	class IMoveable;
	class IScaleable;
	class IRotateable;

	class Vector2D;
	using Coord2D = Vector2D;
	using Size2D = Vector2D;

	class Matrix2;
	class Matrix3;

	bool OE(real x, real y = 0, real e = 0.01);
	int sign(real i);
	const real inversSquareRoot(real len);
}