#include "PrimitiveModel.h"

using namespace AEON_ENGINE;

PrimitiveModel::PrimitiveModel()
{
	loadMesh(m_type);
}

PrimitiveModel::PrimitiveModel(PrimitiveMesh::PrimitiveType primitiveType_)
{
	m_type = primitiveType_;
	loadMesh(primitiveType_);
}

PrimitiveModel::~PrimitiveModel()
{
	//Empty
}

void PrimitiveModel::update(const float deltaTime)
{
	//Empty
}

void PrimitiveModel::render(Shader* shader_)
{
	for (PrimitiveMesh* mesh : m_meshes) {
		mesh->render();
	}
}

bool PrimitiveModel::loadMesh(PrimitiveMesh::PrimitiveType primitiveType_)
{
	m_meshes.push_back(new PrimitiveMesh(primitiveType_));
	return true;
}