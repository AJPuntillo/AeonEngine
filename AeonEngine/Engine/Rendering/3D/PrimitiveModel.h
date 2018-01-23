#ifndef PRIMITIVEMODEL_H
#define PRIMITIVEMODEL_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "PrimitiveMesh.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"
#include "../../Physics/AABB.h"

#include <vector>

namespace AEON_ENGINE {

	class PrimitiveModel : public Entity
	{
	public:
		PrimitiveModel();
		PrimitiveModel(const int primitiveType_, const glm::vec3 pos_, char const* diffusePath_, char const* specularPath_);
		PrimitiveModel(const int primitiveType_, const glm::vec3 pos_, char const* diffusePath_);
		PrimitiveModel(const int primitiveType_, char const* diffusePath_, char const* specularPath_);
		PrimitiveModel(const int primitiveType_, const glm::vec3 pos_);
		PrimitiveModel(const int primitiveType_, char const* diffusePath_);
		PrimitiveModel(const int primitiveType_);
		void setupVolume();

		virtual ~PrimitiveModel();

		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		bool loadMesh(const int primitiveType_);
		unsigned int loadTexture(char const *path_);
		PrimitiveMesh* getMesh();

		AABB BoundingBox;


	private:
		std::vector<PrimitiveMesh*> m_meshes;
		unsigned int texture_diffuse = 0;
		unsigned int texture_specular = 0;
	};

}

#endif
