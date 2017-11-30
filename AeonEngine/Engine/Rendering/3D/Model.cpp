#include "Model.h"

using namespace AEON_ENGINE;

Model::Model(const glm::vec3 pos_, std::string const &path_, bool gamma) : gammaCorrection(gamma)
{
	loadModel(path_);
	m_pos = pos_;
	translate(m_pos);
}

Model::Model(std::string const& path_, bool gamma) : gammaCorrection(gamma)
{
	loadModel(path_);
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	translate(m_pos);
}

Model::~Model()
{
	//Empty
}

void Model::rotate(const float angle_, const glm::vec3& vec_)
{
	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle_, vec_);
}

void Model::translate(const glm::vec3& vec_)
{
	m_translateMatrix = glm::translate(m_translateMatrix, vec_);
	m_pos += vec_;
}

void Model::scale(const glm::vec3& vec_)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, vec_);
}

void Model::update(const float deltaTime)
{
	//Empty
}

void Model::render(Shader* shader_)
{
	//Set the Model matrix	
	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
	shader_->setMat4("model", m_modelMatrix);

	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].render(shader_);

	glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture as a precaution

	//Currently the rotation and scale matrices are being reset and redrawn to prevent additive adjustents
	//Not sure if this is extremely inefficient, will have to revisit
	//***The matrices need to be reset when constantly updated
	//m_rotationMatrix = glm::mat4();
}

void Model::loadModel(std::string const& path_)
{
	//Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path_, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	//Error checking
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	//Retrieve the directory path of the filepath
	directory = path_.substr(0, path_.find_last_of('/'));

	//Process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node_, const aiScene* scene_)
{
	//Process each mesh located at the current node
	for (unsigned int i = 0; i < node_->mNumMeshes; i++)
	{
		//The node object only contains indices to index the actual objects in the scene. 
		//The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene_->mMeshes[node_->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene_));
	}
	//After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node_->mNumChildren; i++)
	{
		processNode(node_->mChildren[i], scene_);
	}

}

Mesh Model::processMesh(aiMesh* mesh_, const aiScene* scene_)
{
	//Data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh_->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; //We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		//Positions
		vector.x = mesh_->mVertices[i].x;
		vector.y = mesh_->mVertices[i].y;
		vector.z = mesh_->mVertices[i].z;
		vertex.position = vector;
		//Normals
		vector.x = mesh_->mNormals[i].x;
		vector.y = mesh_->mNormals[i].y;
		vector.z = mesh_->mNormals[i].z;
		vertex.normal = vector;
		//Texture coordinates
		if (mesh_->mTextureCoords[0]) //Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			//A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			//Use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh_->mTextureCoords[0][i].x;
			vec.y = mesh_->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		//Tangent
		vector.x = mesh_->mTangents[i].x;
		vector.y = mesh_->mTangents[i].y;
		vector.z = mesh_->mTangents[i].z;
		vertex.tangent = vector;
		//Bitangent
		vector.x = mesh_->mBitangents[i].x;
		vector.y = mesh_->mBitangents[i].y;
		vector.z = mesh_->mBitangents[i].z;
		vertex.bitangent = vector;
		vertices.push_back(vertex);
	}
	//Now go through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices
	for (unsigned int i = 0; i < mesh_->mNumFaces; i++)
	{
		aiFace face = mesh_->mFaces[i];
		//Retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	//Process materials
	aiMaterial* material = scene_->mMaterials[mesh_->mMaterialIndex];
	//We assume a convention for sampler names in the shaders. Each diffuse texture should be named
	//As 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 

	//Diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//Specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//Normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	//Height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	//Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

unsigned int Model::loadTextureFromFile(const char* path_, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path_);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path_ << std::endl;
		stbi_image_free(data);
	}

	glBindTexture(GL_TEXTURE_2D, 0); //As a precaution, unbind the texture after it has been created
	return textureID;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat_, aiTextureType type_, std::string typeName_)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat_->GetTextureCount(type_); i++)
	{
		aiString str;
		mat_->GetTexture(type_, i, &str);
		//Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   //If texture hasn't been loaded already, load it
			Texture texture;
			texture.id = loadTextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName_;
			texture.path = str;
			textures.push_back(texture);
			textures_loaded.push_back(texture);  //Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}