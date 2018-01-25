#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "ResourceManager.h"
#include "../Rendering/3D/Model.h"

namespace AEON_ENGINE {

	class ModelManager
	{
	public:
		ModelManager();
		~ModelManager();

		typedef ResourceHandle<Model> HandleType;

		ModelManager::HandleType addModel(const std::string &name_, const std::string &modelPath_);
		ModelManager::HandleType storeModel(const Model* model_, const std::string &name_);
		void deleteModel(const std::string &name_);

		//Getters
		static ModelManager* getInstance();
		Model* getModel(ModelManager::HandleType& handle_);
		Model* getModel(std::string& name_);

	private:
		ResourceManager<Model> m_modelResources;
		static ModelManager* m_instance;
	};

}

#endif