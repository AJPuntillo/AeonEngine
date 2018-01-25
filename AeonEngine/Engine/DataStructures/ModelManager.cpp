#include "ModelManager.h"

using namespace AEON_ENGINE;

ModelManager* ModelManager::m_instance = nullptr;

ModelManager::ModelManager()
{
	//Empty
}

ModelManager::~ModelManager()
{
	m_modelResources.clearKeysAndValues();
}

ModelManager* ModelManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ModelManager();
	}
	return m_instance;
}

ModelManager::HandleType ModelManager::addModel(const std::string &name_, const std::string &modelPath_)
{
	ModelManager::HandleType result;

	Model* model = new Model(modelPath_);
	result = storeModel(model, name_);

	return result;
}

ModelManager::HandleType ModelManager::storeModel(const Model* model_, const std::string &name_)
{
	ModelManager::HandleType result(-1);

	//Is name already in use?
	result = m_modelResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Model name in use");
	}

	result = m_modelResources.put((std::string&)name_, (Model*)model_);
	return result;
}

void ModelManager::deleteModel(const std::string &name_)
{
	HandleType result = m_modelResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Model not found");
	}
	m_modelResources.remove((std::string&)name_);
}

Model* ModelManager::getModel(ModelManager::HandleType& handle_)
{
	if (handle_.isNull()) throw std::string("NULL handle");

	Model* result = m_modelResources.get(handle_);

	if (result == NULL)
		throw std::string("Invalid handle");

	return result;
}

Model* ModelManager::getModel(std::string& name_)
{
	Model* result = NULL;
	ModelManager::HandleType handle = m_modelResources.get(name_);

	if (handle.isNull())
		throw std::string("Model name unknown");

	result = getModel(handle);

	return result;
}