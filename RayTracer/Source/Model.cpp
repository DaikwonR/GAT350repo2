#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Model::Update()
{
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		m_vertices[i] = m_transform * glm::vec4{ m_local_vertices[i], 1 };
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
					m_local_vertices.push_back(position);
				}
			}
		}
	}

	m_vertices.resize(m_local_vertices);

	stream.close();
	return false;
}

bool Model::Hit(const ray_t& ray, raycastHit_t* raycastHit, float minDistance, float maxDistance)
{
	for (size_t i = 0; i < m_vertices.size(); i += 3)
	{
		float t;
		if (Triangle::RayCast(ray, m_vertices[i], m_vertices[i + 1], m_vertices[i + 2], minDistance, maxDistance, t))
		{
			raycastHit->distance = t;
			raycastHit->point = ray.at(t);

			glm::vec3 edge = 
		}
	}
	return false;
}

