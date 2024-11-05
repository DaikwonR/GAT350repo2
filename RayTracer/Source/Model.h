#pragma once

#include "Color.h"
#include "Material.h"
#include "Triangle.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model : public SceneObject
{
public:

	Model() = default;
	Model(const Transform& transform, std::shared_ptr<Material> material) : 
		SceneObject{ transform, material }
	{}
	
	void Update() override;
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

	bool Load(const std::string& filename);

private:
	vertices_t m_vertices;
	vertices_t m_local_vertices;
};
