#pragma once

#include "Color.h"

struct fragment_input_t
{
	glm::vec3 postion;
	glm::vec3 normal;
	color4_t color;
};

class FragmentShader
{
public:
	static color4_t Process(const fragment_input_t& fragment);
};