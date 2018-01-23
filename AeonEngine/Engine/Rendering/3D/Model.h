#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include "Entity.h"
#include "Mesh.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"

#include <string>
#include <map>

namespace AEON_ENGINE {

	class Model : public Entity
	{
	public:
		//Expects a filepath to a 3D model.
		Model(const glm::vec3 pos_, std::string const& path_, bool gamma = false);
		Model(std::string const& path_, bool gamma = false);
		~Model();

		//Matrix manipulation
		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		//Updating and rendering
		void update(const float deltaTime_) override;
		void render(Shader* shader_) override;

		//Model Data
		std::vector<Texture> textures_loaded; //Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;

	private:
		//Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(std::string const& path_);
		//Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode* node_, const aiScene* scene_);
		Mesh processMesh(aiMesh* mesh_, const aiScene* scene_);
		unsigned int loadTextureFromFile(const char* path_, const std::string& directory_, bool gamma = false);
		//Checks all material textures of a given type and loads the textures if they're not loaded yet
		//The required info is returned as a Texture struct
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat_, aiTextureType type_, std::string typeName_);
	};

}

#endif