#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"
#include "Model.h"
#include "Transform.h"
#include "../../DataStructures/ShaderManager.h"
#include "../../Physics/BoundingVolume.h"
#include "../Particles/ParticleEngine.h"

namespace AEON_ENGINE {

	class GameObject : public Entity
	{
	public:
		GameObject(glm::vec3 pos_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4 rot_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		GameObject(std::string modelPath_);
		GameObject(Mesh::PrimitiveType primitiveType_);
		GameObject(int amount, float lifespan);
		~GameObject();

		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		void attachModel(Entity* model_);
		void detachModel();
		void attachShader(ShaderManager::HandleType shaderHandle_);
		void attachMaterial(/*Material* mat_*/);

		void setupVolume();

		//Getters
		Entity* getAttachedModel() const { return m_model; }
		Shader* getAttachedShader() const {
			Shader* temp = ShaderManager::getInstance()->getShader(m_shader);
			return temp;
		}
		//Material* getAttachedMaterial() const { return m_material; }
		glm::mat4 getModelMatrix() const { return transform.modelMatrix; }

		//Transformations
		Transform transform;

		//Bounding Volume
		BoundingVolume* boundingVolume;

	private:
		Entity* m_model = nullptr;
		ShaderManager::HandleType m_shader;
		//Material* m_material;
	};

}

#endif