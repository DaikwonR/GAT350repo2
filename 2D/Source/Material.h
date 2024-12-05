#pragma once

#include "Color.h"
#include <glm\glm.hpp>

struct material_t
{
	color3_t albedo{ 1 };
	color3_t specular{ 1 };
	float shininess{ 32 };
};