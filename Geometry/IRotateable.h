#pragma once
#include "Geometry.def.h"

namespace gm {
	class IRotateable {
	public:
		virtual void rotate(angle a)abstract;
		virtual const angle getRotation()const abstract;
		virtual void setRotation(const angle& ang);
		virtual ~IRotateable();
	};
}