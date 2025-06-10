#ifndef UTILS_H
#define UTILS_H

#include <glm.hpp>
#include "RenderUtils.h"

namespace dae
{
	struct Rect
	{
		int x;
		int y;
		int w;
		int h;
	};

	template<typename VecType>
	auto LengthSquared(const VecType& v) -> decltype(glm::dot(v, v))
	{
		return glm::dot(v, v);
	}
}

#endif // UTILS_H