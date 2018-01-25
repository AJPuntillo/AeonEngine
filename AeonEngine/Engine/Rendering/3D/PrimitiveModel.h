#ifndef PRIMITIVEMODEL_H
#define PRIMITIVEMODEL_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "PrimitiveMesh.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"

#include <vector>

namespace AEON_ENGINE {

	class PrimitiveModel : public Entity
	{
	public:
		PrimitiveModel();
		PrimitiveModel(PrimitiveMesh::PrimitiveType primitiveType_);

		virtual ~PrimitiveModel();

		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		bool loadMesh(PrimitiveMesh::PrimitiveType primitiveType_);

	private:
		std::vector<PrimitiveMesh*> m_meshes;
		PrimitiveMesh::PrimitiveType m_type = PrimitiveMesh::PrimitiveType::CUBE;
	};

}

#endif
