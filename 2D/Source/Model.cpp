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
		
		if (s1.x == -1 || s1.y == -1 || s2.x == -1 || s2.y == -1 || s3.x == -1 || s3.y == -1)
		{
			continue;
		}

		framebuffer.DrawTriangle(s1.x, s1.y, s2.x, s2.y, s3.x, s3.y, m_color);
	}
}

bool Model::Load(const std::string& filename)
{
	std::ifstream stream(filename);
	// check if stream is_open
	if (!stream.is_open())
	{
		std::cerr << "Error opening" << filename;
		return false;
	}
	vertices_t vertices;
	std::string line;
	while (std::getline(stream, line))
	{
		
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream sstream{ line.substr(2) };
			glm::vec3 position;
			sstream >> position.x;
			sstream >> position.y;
			sstream >> position.z;

			vertices.push_back(position);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream sstream{ line.substr(2) };
			std::string str;
			while (std::getline(sstream, str, ' '))
			{
				std::istringstream sstream(str);
				std::string indexString;

				// read each triangle index
				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 }; // position, normal, uv
				while (std::getline(sstream, indexString, '/'))
				{
					if (!indexString.empty())
					{
						std::istringstream indexStream{ indexString };
						indexStream >> index[i];
					}
					i++;
				}

				// check if index is valid (not 0)
				if (index[0])
				{
					// get vertex at index position
					glm::vec3 position = vertices[index[0] - 1];
					// add vertex to model vertices
					m_vertices.push_back(position);
				}
			}
		}
	}
	stream.close();
	return false;
}
