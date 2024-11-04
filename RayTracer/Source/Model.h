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
		SceneObject{ transform },
		SceneObject{ material } 
	{}
	
	Model(std::shared_ptr<Material> material) : 
		SceneObject{ material } 
	{}

	Model(const vertices_t& vertices, std::shared_ptr<Material> material) : 
		SceneObject{ material },
		m_vertices{ vertices }
	{}


	
	bool Load(const std::string& filename);
	bool Hit(const ray_t& ray, raycastHit_t* raycastHit, float minDistance, float maxDistance) override;
	

	void SetColor(const color_t& color) { m_color = color; }

private:
	vertices_t m_vertices;
	vertices_t m_local_vertices;

	// Inherited via SceneObject
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;
	void Update() override;
};
