#include "Geometry.def.h"
#include "Vector.h"

namespace gm {

	bool OE(real x, real y, real e) {
		return abs(x - y) < e;
	}
	int sign(real i) {
		if (i > 0) { return 1; }
		if (i < 0) { return -1; }
		return 0;
	}
	const real inversSquareRoot(real len) {
		return 1. / sqrt(len);
		real y = len;
		real x2 = y * 0.5;
		std::int64_t i = *(std::int64_t*)&y;
		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(real*)&i;
		y = y * (1.5 - (x2 * y * y));   // 1st iteration
		//      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
		return y;
	}
	angle smallestAng(const gm::Vector& v, const gm::Vector& u) {
		auto a = abs(v ^ u);
		return a <= PI ? a : PI2 - a;
	}
}