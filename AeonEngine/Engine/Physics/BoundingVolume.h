#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <glm/glm.hpp>

#include "../Rendering/3D/Model.h"

namespace AEON_ENGINE {

	class BoundingVolume
	{
	public:
		BoundingVolume();
		BoundingVolume(glm::vec3 &minCorner_, glm::vec3 &maxCorner_);
		~BoundingVolume();

		void setupVolume(Model* model_);
		bool isColliding(const BoundingVolume &bv) const;
		void movedBy(glm::vec3 &amount_);

		//Getters
		glm::vec3 getPositiveVertex(glm::vec3 &norm);
		glm::vec3 getNegativeVertex(glm::vec3 &norm);
		glm::vec3 getMinCorner() const { return m_minCorner; }
		glm::vec3 getMaxCorner() const { return m_maxCorner; }

	private:
		glm::vec3 m_minCorner;
		glm::vec3 m_maxCorner;
	};

}

#endif