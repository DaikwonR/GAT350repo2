#pragma once

#include "Material.h"
#include "Ray.h"

#include <memory>
#include "Transform.h"

class SceneObject
{
public:
	//SceneObject() = default;
	SceneObject(const Transform& transform, std::shared_ptr<Material> material) : 
		m_transform{ transform },
		m_material{ material } 
	{}

	virtual bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) = 0;

	std::weak_ptr<Material> GetMaterial() { return m_material; }

	virtual void Update() = 0;

private:

	const Transform& m_transform;
	std::shared_ptr<Material> m_material;
};