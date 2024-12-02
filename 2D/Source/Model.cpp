#include "Model.h"
#include "Framebuffer.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>



void Model::Draw()
{
	Shader::Draw(m_vb);
	
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
	//vertices_t vertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
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
		else if (line.substr(0, 3) == "vn ")
		{
			std::istringstream sstream{ line.substr(3) };
			glm::vec3 normal;
			sstream >> normal.x;
			sstream >> normal.y;
			sstream >> normal.z;

			normals.push_back(normal);
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
					vertex_t vertex;
					vertex.position = vertices[index[0] - 1];
					vertex.normal = (index[2]) ? normals[index[2] - 1] : glm::vec3{ 1 };

					// add vertex to model vertices
					m_vb.push_back(vertex);
				}
			}
		}
	}
	stream.close();
	return false;
}

void Model::Draw()
{
	Shader::Draw(m_vb);
}

void Model::SetColor(const color4_t& color)
{
	m_color = color;
}