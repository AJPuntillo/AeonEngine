#include "BoundingVolume.h"

using namespace AEON_ENGINE;

BoundingVolume::BoundingVolume() :
	m_minCorner(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_maxCorner(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

BoundingVolume::BoundingVolume(glm::vec3 &minCorner_, glm::vec3 &maxCorner_)
{
	m_minCorner = minCorner_;
	m_maxCorner = maxCorner_;
}

BoundingVolume::~BoundingVolume()
{
}

void BoundingVolume::setupVolume(Model* model_) {
	
	for (int i = 0; i < model_->meshes.size(); i++) {
		std::vector<Vertex> vertexList = model_->meshes[i].getVertices();
		bool firstSet = true;

		for (int j = 0; j < vertexList.size(); j++) {
			if (firstSet) {
				m_maxCorner[0] = vertexList[j].position[0];
				m_maxCorner[1] = vertexList[j].position[1];
				m_maxCorner[2] = vertexList[j].position[2];
				m_minCorner[0] = vertexList[j].position[0];
				m_minCorner[1] = vertexList[j].position[1];
				m_minCorner[2] = vertexList[j].position[2];
				firstSet = false;
			}
			else {
				if (vertexList[j].position[0] > m_maxCorner[0]) m_maxCorner[0] = vertexList[j].position[0];
				if (vertexList[j].position[1] > m_maxCorner[1]) m_maxCorner[1] = vertexList[j].position[1];
				if (vertexList[j].position[2] > m_maxCorner[2]) m_maxCorner[2] = vertexList[j].position[2];

				if (vertexList[j].position[0] < m_minCorner[0]) m_minCorner[0] = vertexList[j].position[0];
				if (vertexList[j].position[1] < m_minCorner[1]) m_minCorner[1] = vertexList[j].position[1];
				if (vertexList[j].position[2] < m_minCorner[2]) m_minCorner[2] = vertexList[j].position[2];
			}
		}
	}
}

bool BoundingVolume::isColliding(const BoundingVolume &bv) const
{
	if (((glm::vec3)m_minCorner)[0] > ((BoundingVolume&)bv).m_maxCorner[0]) return false;
	if (((glm::vec3)m_minCorner)[1] > ((BoundingVolume&)bv).m_maxCorner[1]) return false;
	if (((glm::vec3)m_minCorner)[2] > ((BoundingVolume&)bv).m_maxCorner[2]) return false;

	if (((glm::vec3)m_maxCorner)[0] < ((BoundingVolume&)bv).m_minCorner[0]) return false;
	if (((glm::vec3)m_maxCorner)[1] < ((BoundingVolume&)bv).m_minCorner[1]) return false;
	if (((glm::vec3)m_maxCorner)[2] < ((BoundingVolume&)bv).m_minCorner[2]) return false;

	return true;
}

void BoundingVolume::movedBy(glm::vec3 &amount_)
{
	//BoundingVolume* result(this);
	//result->m_minCorner = result->m_minCorner + amount_;
	//result->m_maxCorner = result->m_maxCorner + amount_;
	//return result;
	m_minCorner += amount_;
	m_maxCorner += amount_;
}

glm::vec3 BoundingVolume::getPositiveVertex(glm::vec3 &norm)
{
	glm::vec3 result(m_minCorner);

	if (norm[0] > 0) result[0] = m_maxCorner[0];
	if (norm[1] > 0) result[1] = m_maxCorner[1];
	if (norm[2] > 0) result[2] = m_maxCorner[2];

	return result;
}

glm::vec3 BoundingVolume::getNegativeVertex(glm::vec3 &norm)
{
	glm::vec3 result(m_minCorner);

	if (norm[0] < 0) result[0] = m_minCorner[0];
	if (norm[1] < 0) result[1] = m_minCorner[1];
	if (norm[2] < 0) result[2] = m_minCorner[2];

	return result;
}