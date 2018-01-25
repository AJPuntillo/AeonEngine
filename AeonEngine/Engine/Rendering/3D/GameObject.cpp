#include "GameObject.h"

using namespace AEON_ENGINE;

GameObject::GameObject(glm::vec3 pos_, glm::vec3 scale_, glm::vec4 rot_)
{
	transform.translateBy(pos_);
	transform.scaleBy(scale_);
	transform.rotateBy(rot_);
}

GameObject::GameObject(std::string modelPath_)
{
	m_model = new Model(modelPath_);
}

GameObject::GameObject(PrimitiveMesh::PrimitiveType primitiveType_)
{
	m_model = new PrimitiveModel(primitiveType_);
}

GameObject::~GameObject()
{

}

void GameObject::update(const float deltaTime)
{

}

void GameObject::render(Shader* shader_)
{
	//Set the Model matrix
	transform.updateModelMatrix();
	shader_->setMat4("model", transform.modelMatrix);

	//Render the model
	m_model->render(shader_);
}

void GameObject::attachModel(Entity* model_)
{
	if (m_model != nullptr)
		std::cout << "Model already attached to GameObject!" << std::endl;
	else
		m_model = model_;
}

void GameObject::detachModel()
{
	m_model = nullptr;
}

void GameObject::attachShader(ShaderManager::HandleType shaderHandle_)
{
	if (!m_shader.isNull())
		std::cout << "Shader already attached to GameObject!" << std::endl;
	else
		m_shader = shaderHandle_;
}

void GameObject::attachMaterial(/*Material* mat_*/)
{

}