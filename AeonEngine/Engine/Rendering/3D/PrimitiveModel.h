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
		PrimitiveModel(const glm::vec3 pos_, char const* diffusePath_, char const* specularPath_);
		PrimitiveModel(const glm::vec3 pos_, char const* diffusePath_);
		PrimitiveModel(char const* diffusePath_, char const* specularPath_);
		PrimitiveModel(const glm::vec3 pos_);
		PrimitiveModel(char const* diffusePath_);

		virtual ~PrimitiveModel();

		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		bool loadMesh();
		unsigned int loadTexture(char const *path_);

	private:
		std::vector<PrimitiveMesh*> m_meshes;
		unsigned int texture_diffuse = 0;
		unsigned int texture_specular = 0;
	};

}

#endif
