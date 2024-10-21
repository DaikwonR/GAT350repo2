#include "Framebuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"

#include <iostream>

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
	if (m_texture == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(width * height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	color_t& dest = m_buffer[x + y * m_width];
	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawPointClip(int x, int y, const color_t& color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
	
	color_t& dest = m_buffer[x + y * m_width];
	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawRect(int x, int y, int width, int height, const color_t& color)
{
	if (x + width < 0 || x >= m_width, y + height < 0 || y >= m_height) return;

	int x1 = std::max(x, 0);
	int x2 = std::min(x + width, m_width);
	int y1 = std::max(y, 0);
	int y2 = std::min(y + height, m_height);


	for (int sy = y1; sy < y2; sy++)
	{
		int index = x1 + sy * m_width;
		//std::fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1), color);
		//for (int sx = x1; sx < x2; sx++) 
		{
			// m_buffer[sx + sy * m_width] = color;
			// m_buffer[index++] = color;
		}
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{

	// Calculate the difference in x coords between the two points
	int dx = x2 - x1;
	// Calculate the difference in y coords between the two points
	int dy = y2 - y1;

	// Determine if the line is steep (if the absolute difference in y is greater than the absolute difference in x)
	bool steep = (std::abs(dy) > std::abs(dx));
	// If the line is steep, swap the roles of x and y for both points to simplify calculation
	if (steep)
	{
		//DrawPointClip(x, y, color);
		std::swap(x1, y1); // Swap x1 and y1 to make calculations easier for steep lines
		std::swap(x2, y2); // Swap x2 and y2 to maintain consistency after swapping
	}
	// Ensure that we always draw from left to right by swapping points if necessary
	// x1 and y1 represent the starting point of the line.
	// x2 and y2 represent the ending point of the line.
	if (x1 > x2)
	{
		std::swap(x1, x2); // Swap x1 and x2 so that x1 is always the smaller value, ensuring we draw from left to right
		std::swap(y1, y2); // Swap y1 and y2 to keep the relationship between points consistent
	}

	// Re-establish dx and dy after any swapping to ensure they are based on the updated coordinates
	dx = x2 - x1;
	// Calculate the absolute value of dy, since we need a positive difference for the error term.
	dy = std::abs(y2 - y1);

	// Initialize the error term, starting at half of dx to ensure balanced stepping.
	// How far off the current pixel is from the ideal line the we wat to draw the next pixel.
	int error = dx / 2;
	// Determine the direction of y movement (either +1 or -1)
	// ystep determines whether y should increase or decrease or decrease as x increases.
	// if y1 < y2, the line moves upwards, so ystep = 1. Otherwise, ystep = -1 for downward movement
	int ystep = (y1 < y2) ? 1 : -1;

	for (int x = x1, y = y1; x <= x2; x++)
	{
		// If the line is steep, swap x and y when drawing the point to ensure correctness
		// We swap x and y to ensure consistency, because if steep is true that means it changed more in the y direction
		(steep) ? DrawPointClip(y, x, color) : DrawPointClip(x, y, color);

		// Subtract dy from the error term
		error -= dy;

		// update error term
		if (error < 0)
		{
			y += ystep; // Move y int the appropriate direction (up or down)
			error += dx; // Reset error for the next step
		}
	}
}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	// Calculate the difference in x coords between the two points
	int dx = x2 - x1;
	// Calculate the difference in y coords between the two points
	int dy = y2 - y1;

	// Handle the case when the line is vertical (dx == 0)
	if (dx == 0)
	{
		// Ensure that y1 is less than y2, swap if needed to draw in the correct direction
		if (y1 > y2) std::swap(y1, y2);
		// Iterate over the y values to draw a vertical line
		for (int y = y1; y < y2; y++)
		{
			// Set the color for each point along the vertical line
			m_buffer[x1 + y * m_width] = color;
		}
	}
	else
	{
		// Calculate the slope of the line (m). Cast to float to ensure floating-point division
		float m = dy / (float)dx;
		// Calculate the y intercept (b) using y = mx + b, rearranged to solve for b
		float b = y1 - (m * x1);

		// run > rise
		if (std::abs(dx) > std::abs(dy))
		{
			// Iterate over the y values to draw a vertical line
			for (int x = x1; x < x2; x++)
			{
				// y = mx + b
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;

			}
		}
		else
		{
			// rise > run
			for (int y = y1; y < y2; y++)
			{
				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;

			}
		}
	}
	
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawCircle(int xc, int yc, int radius, const color_t& color)
{

	// The current start point of the edge of the circle int the x direction
	int x = 0;
	//The initial pint at the top of the circle in the y direction
	int y = radius;
	// "decision parameter", helps decide whether the next point moves horizontally or diagonally
	int p = 1 - radius;
	
	// Draw the initial point in all eight octants of the circle
	// This draws points using the symmetry of the circle
	DrawPoint(xc + x, yc + y, color); // Top right
	DrawPoint(xc - x, yc + y, color); // Top left
	DrawPoint(xc + x, yc - y, color); // Bottom right
	DrawPoint(xc - x, yc - y, color); // Bottom left
	DrawPoint(xc + y, yc + x, color); // Right top
	DrawPoint(xc - y, yc + x, color); // Left top
	DrawPoint(xc + y, yc - x, color); // Right bottom
	DrawPoint(xc - y, yc - x, color); // Left bottom

	// Draws the circle until x and y intersect
	while (x < y)
	{
		x++;
		// If the decision parameter is negative, the next poit remains within the circle boundary
		if (p < 0)
		{
			// Update the decision parameter to move to the next horizontal point
			p += 2 * x + 1;
		}
		else
		{

			y--;
			// Update the decision parameter when moving diagonally (right and down)
			p += 2 * (x - y) + 1;
		}

		// Draw the points in all eight octants for the current x and y
		// This ensures the full symmetry of the circle
		DrawPoint(xc + x, yc + y, color); // Top right
		DrawPoint(xc - x, yc + y, color); // Top left
		DrawPoint(xc + x, yc - y, color); // Bottom right
		DrawPoint(xc - x, yc - y, color); // Bottom left
		DrawPoint(xc + y, yc + x, color); // Right top
		DrawPoint(xc - y, yc + x, color); // Left top
		DrawPoint(xc + y, yc - x, color); // Right bottom
		DrawPoint(xc - y, yc - x, color); // Left bottom
	}
}

void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{
	float dt = 1.0f / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{

		int sx1 = Lerp(x1, x2, t1);
		int sy1 = Lerp(y1, y2, t1);

		float t2 = t1 + dt;

		int sx2 = Lerp(x1, x2, t2);
		int sy2 = Lerp(y1, y2, t2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1.0f / 100.0f;
	float t1 = 0;
	for (int i = 0; i < 100; i++)
	{
		int sx1, sy1;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);

		float t2 = t1 + dt;

		int sx2, sy2;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawCubicSpline(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1.0f / 100.0f;
	float t1 = 0;
	for (int i = 0; i < 100; i++)
	{
		int sx1, sy1;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);

		float t2 = t1 + dt;

		int sx2, sy2;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawImage(int x, int y, const Image& image)
{
	// check if off-screen
	if (x + m_width < 0 || x >= m_width, y + m_height < 0 || y >= m_height) return;

	// iterate through image y
	for (int iy = 0; iy < image.m_height; iy++)
	{
		// set screen y
		int sy = y + iy;
		// check if off-screen, don't draw if off screen
		if (sy < 0 || sy >= m_height) continue;

		for (int ix = 0; ix < image.m_width; ix++)
		{
			int sx = ix + x;

			if (sx < 0 || sx >= m_width) continue;

			color_t color = image.m_buffer[ix + (iy * image.m_width)];

			// if (color.a == 0) continue;
			DrawPoint(sx, sy, color);

			//m_buffer[sx + sy * m_width] = color;
		}	
	}
}

void Framebuffer::DrawImage(int x, int y, int w, int h, const Image& image)
{
}
