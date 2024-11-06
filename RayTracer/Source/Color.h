#pragma once

#include "MathUtils.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/color_space.hpp>

using color_t = SDL_Color;
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color_t ColorConvert(const color4_t& color4)
{
	color_t color;

	color.r = (uint8_t)(Clamp(color4.r, 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(Clamp(color4.g, 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(Clamp(color4.b, 0.0f, 1.0f) * 255);
	color.a = (uint8_t)(Clamp(color4.a, 0.0f, 1.0f) * 255);

	return color;
}

inline color_t ColorConvert(const color3_t& color3)
{
	color_t color;

	color.r = (uint8_t)(Clamp(color3.r, 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(Clamp(color3.g, 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(Clamp(color3.b, 0.0f, 1.0f) * 255);
	color.a = 255;

	return color;
}

inline color4_t ColorConvert(const color_t& color)
{
	color4_t color4;

	color4.r = color.r / 255.0f;
	color4.g = color.g / 255.0f;
	color4.b = color.b / 255.0f;
	color4.a = color.a / 255.0f;

	return color4;
}

inline color3_t HSVtoRGB(const glm::vec3& hsv)
{
	return glm::rgbColor(hsv);
}

inline color3_t HSVtoRGB(float hue, float saturation, float value)
{
	return glm::rgbColor(glm::vec3{ hue, saturation, value });
}

inline float LinearToGamma(float linear)
{
	if (linear > 0)
		return std::sqrt(linear);

	return 0;
}

enum class BlendMode
{
	Normal,
	Alpha,
	Additive,
	Multiply
};

inline color_t NormalBlend(const color_t& src, const color_t& dest);
inline color_t AlphaBlend(const color_t& src, const color_t& dest);
inline color_t AdditiveBlend(const color_t& src, const color_t& dest);
inline color_t MultiplyBlend(const color_t& src, const color_t& dest);

void SetBlendMode(BlendMode blendMode);
color_t ColorBlend(const color_t& src, const color_t& dest);

