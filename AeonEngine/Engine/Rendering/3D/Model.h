#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "Mesh.h"
#include "../../Camera/Camera.h"

#include <vector>

namespace AEON_ENGINE {

	class Model : public Entity
	{
	public:
		Model(const glm::vec3 pos_);
		virtual ~Model();

		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		bool loadMesh(/*const char* filename*/);
		void update(const float deltaTime);
		void render(Shader* shader_);

	private:
		std::vector<Mesh*> m_meshes;
	};

}

#endif