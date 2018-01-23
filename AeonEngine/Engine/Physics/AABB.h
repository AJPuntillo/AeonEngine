#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace AEON_ENGINE {
	class AABB
	{
	public:

		// AABB using min and max 
		AABB() {
			min = glm::vec3(-0.5, -0.5, -0.5);
			max = glm::vec3(0.5, 0.5, 0.5);
		}

		//given min and max
		AABB(glm::vec3 _min, glm::vec3 _max) {
			min = _min;
			max = _max;
		}

		AABB(glm::vec3 centerPoint, float radius) {
			min.x = centerPoint.x - radius;
			min.y = centerPoint.y - radius;
			min.z = centerPoint.z - radius;

			max.x = centerPoint.x + radius;
			max.y = centerPoint.y + radius;
			max.z = centerPoint.z + radius;
		}

		AABB CenterThreeFloats(glm::vec3 centerPoint, float _x, float _y, float _z) {
			min.x = centerPoint.x - _x;
			min.y = centerPoint.y - _y;
			min.z = centerPoint.z - _z;

			max.x = centerPoint.x + _x;
			max.y = centerPoint.y + _y;
			max.z = centerPoint.z + _z;
		}

		AABB MinThreeFloats(glm::vec3 _min, float _x, float _y, float _z) {
			min = _min;
			max.x = _min.x + _x;
			max.y = _min.y + _y;
			max.z = _min.z + _z;
		}

		int TestAABBAABBMinMax(AABB a, AABB b);
		//float d[3]; 
		//center point
		// glm::vec3 center;
		//halfway
		//float r[3]

		glm::vec3 min;
		glm::vec3 max;
		//radius
		float r;

	private:


		/*int TestAABBAABB(AABB a, AABB b)
		{
			float t;
			if ((t = a.min[0] - b.min[0]) > b.d[0] || -t > a.d[0]) return 0;
			if ((t = a.min[1] - b.min[1]) > b.d[1] || -t > a.d[1]) return 0;
			if ((t = a.min[2] - b.min[2]) > b.d[2] || -t > a.d[2]) return 0;
			return 1;
		}


		int TestAABBAABB(AABB a, AABB b)
		{
			if (Abs(a.c[0] - b.c[0]) > (a.r[0] + b.r[0])) return 0;
			if (Abs(a.c[1] - b.c[1]) > (a.r[1] + b.r[1])) return 0;
			if (Abs(a.c[2] - b.c[2]) > (a.r[2] + b.r[2])) return 0;
			return 1;
		}*/



		int TestAABBAABBHalfWay(AABB a, AABB b);

	};
}

