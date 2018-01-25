#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "ResourceManager.h"
#include "../Graphics/Shader.h"

namespace AEON_ENGINE {

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		typedef ResourceHandle<Shader> HandleType;

		ShaderManager::HandleType addShader(const std::string &name_, const std::string &vertexPath_, const std::string &fragmentPath_);
		ShaderManager::HandleType storeShader(const Shader* shader_, const std::string &name_);
		void deleteShader(const std::string &name_);

		//Getters
		static ShaderManager* getInstance();
		ShaderManager::HandleType getShader(const std::string &name_);
		Shader* getShader(const ShaderManager::HandleType &handle_);

	private:
		ResourceManager<Shader> m_ShaderResources;
		static ShaderManager* m_instance;
	};

}

#endif