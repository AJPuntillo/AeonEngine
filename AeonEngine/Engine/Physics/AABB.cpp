#include "AABB.h"

using namespace AEON_ENGINE;

int AABB::TestAABBAABBMinMax(AABB a, AABB b)
{
	// if true then no intersection
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return 0;
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return 0;
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return 0;
	// Overlapping on all axes means the two AABBs are intersecting
	std::cout << "collision" << std::endl;
	return 1;
}


//int TestAABBAABB(AABB a, AABB b)
//{
//	float t;
//	if ((t = a.min[0] - b.min[0]) > b.d[0] || -t > a.d[0]) return 0;
//	if ((t = a.min[1] - b.min[1]) > b.d[1] || -t > a.d[1]) return 0;
//	if ((t = a.min[2] - b.min[2]) > b.d[2] || -t > a.d[2]) return 0;
//	return 1;
//}
//
//
//int TestAABBAABB(AABB a, AABB b)
//{
//	if (Abs(a.c[0] - b.c[0]) > (a.r[0] + b.r[0])) return 0;
//	if (Abs(a.c[1] - b.c[1]) > (a.r[1] + b.r[1])) return 0;
//	if (Abs(a.c[2] - b.c[2]) > (a.r[2] + b.r[2])) return 0;
//	return 1;
//}
//
//
//overlap = (unsigned int)(B - C) <= (B - A) + (D - C);

//int AABB::TestAABBAABBHalfWay(AABB a, AABB b)
//{
//	int r;
//	r = a.r[0] + b.r[0]; if ((unsigned int)(a.c[0] - b.c[0] + r) > r + r) return 0;
//	r = a.r[1] + b.r[1]; if ((unsigned int)(a.c[1] - b.c[1] + r) > r + r) return 0;
//	r = a.r[2] + b.r[2]; if ((unsigned int)(a.c[2] - b.c[2] + r) > r + r) return 0;
//	return 1;
//}
//
//void AABB::setupVolume(PrimitiveModel model_) {
//
//	PrimitiveMesh *temp = model_.getMesh();
//	std::vector<PrimitiveVertex> vertexList = *temp->getVerticies();
//
//
//	bool firstSet = true;
//
//	int componentListSize = vertexList.size();
//
//
//	
//	min = vertexList[0].position;
//	max = vertexList[0].position;
//	for (int i = 0; i < componentListSize; i++) {
//		if (vertexList[i].position.x < min.x) {
//			min.x = vertexList[i].position.x;
//		}
//		if (vertexList[i].position.y < min.y) {
//			min.y = vertexList[i].position.y;
//		}
//		if (vertexList[i].position.z < min.z) {
//			min.z = vertexList[i].position.z;
//		}
//		if (vertexList[i].position.x > max.x) {
//			max.x = vertexList[i].position.x;
//		}
//		if (vertexList[i].position.y > max.y) {
//			max.y = vertexList[i].position.y;
//		}
//		if (vertexList[i].position.z > max.z) {
//			max.z = vertexList[i].position.z;
//		}
//
//	}
//	//for (int i = 0; i < componentListSize; i++)
//	//{
//	//	VertexComponentDescriptor vertexDesc = model_.getMesh()->vertexDescriptor->componentList[i];
//	//	if (vertexDesc.type == VertexComponentDescriptor::VC_POSITION_3F)
//	//	{
//	//		int offset = vertexDesc.offset;
//	//		int inc = model_.getMesh()->vertexDescriptor->getStride();
//
//	//		//We don't want the whole list, we only want each row of vertices (every position value) -- Therefore divide by the stride value to get the number of vertices in the list
//	//		int numOfVerts = vertexList.size() / inc;
//
//	//		for (int j = 0; j < numOfVerts; j++)
//	//		{
//	//			if (firstSet) {
//	//				m_maxCorner[0] = vertexList[offset];
//	//				m_maxCorner[1] = vertexList[offset + 1];
//	//				m_maxCorner[2] = vertexList[offset + 2];
//	//				m_minCorner[0] = vertexList[offset];
//	//				m_minCorner[1] = vertexList[offset + 1];
//	//				m_minCorner[2] = vertexList[offset + 2];
//	//				firstSet = false;
//	//			}
//	//			else {
//	//				if (vertexList[offset] > m_maxCorner[0]) m_maxCorner[0] = vertexList[offset];
//	//				if (vertexList[offset + 1] > m_maxCorner[1]) m_maxCorner[1] = vertexList[offset + 1];
//	//				if (vertexList[offset + 2] > m_maxCorner[2]) m_maxCorner[2] = vertexList[offset + 2];
//
//	//				if (vertexList[offset] < m_minCorner[0]) m_minCorner[0] = vertexList[offset];
//	//				if (vertexList[offset + 1] < m_minCorner[1]) m_minCorner[1] = vertexList[offset + 1];
//	//				if (vertexList[offset + 2] < m_minCorner[2]) m_minCorner[2] = vertexList[offset + 2];
//	//			}
//	//			offset += inc;
//	//		}
//	//	}
//	//}
//}