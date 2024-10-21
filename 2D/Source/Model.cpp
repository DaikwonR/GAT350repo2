#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>



void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const Camera& camera)
{
	for (int i = 0; i < m_vertices.size(); i += 3)
	{
		// Convert point from model space to world space
		vertex_t p1 = model * glm::vec4{ m_vertices[i + 0], 1 };
		vertex_t p2 = model * glm::vec4{ m_vertices[i + 1], 1 };
		vertex_t p3 = model * glm::vec4{ m_vertices[i + 2], 1 };

		// Convert point from world space to view space
		p1 = camera.ModelToView(p1);
		p2 = camera.ModelToView(p2);
		p3 = camera.ModelToView(p3);

		// Convert point from view space to projection space
		glm::ivec2 s1 = camera.ViewToScreen(p1);
		glm::ivec2 s2 = camera.ViewToScreen(p2);
		glm::ivec2 s3 = camera.ViewToScreen(p3);
		

		framebuffer.DrawTriangle(s1.x, s1.y, s2.x, s2.y, s3.x, s3.y, m_color);
	}
}

bool Model::Load(const std::string& filename)
{
//	std::ifstream stream(filename);
//
//	if (!stream.is_open())
//	{
//		std::cerr << "Error opening" << filename << endl;
//	}
//	vertices_t vertices;
//	std::string line;
//	while (std::getline(stream, line))
//	{
//		if (line.substr)
//		{
//
//		}
//		else if ()
//		{
//
//		}
//	}
	return false;
}
