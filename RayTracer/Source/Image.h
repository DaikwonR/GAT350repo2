#pragma once

#include "Framebuffer.h"

#include <string>
#include <vector>

class Image
{
public:
	Image() = default;
	~Image() = default;

	bool Load(const std::string& filename);
	/*bool Load(const std::string& filename, uint8_t alpha = 255);*/

	friend class Framebuffer;
public:
	uint8_t* buffer{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<color_t> m_buffer;
};