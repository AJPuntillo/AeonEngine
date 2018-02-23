#ifndef TILE_H
#define TILE_H

#include "../3D/Entity.h"
#include "../3D/Model.h"
#include "../3D/Transform.h"
#include "../../Physics/BoundingVolume.h"

namespace AEON_ENGINE {

	class Tile : Entity
	{
	public:

		enum TileType
		{
			GRASS,
			MOUNTAIN,
			FOREST,
			LAVA
		};

		Tile();
		Tile(int tileType_, bool isPrimitive = false);
		~Tile();

		//Updating and rendering
		void update(const float deltaTime_) override;
		void render(Shader* shader_) override;

		void translateTile(float x, float y, float z);
		Transform transform;

		BoundingVolume* m_bound;
		glm::vec3 m_centerPos;
		float m_xOffset = 0; //Width of bounding volume
		float m_zOffset = 0; //Length of bounding volume

	protected:
		void setupTile();
		void calcCenterPosition();
		void calcOffsets();

		Model* m_tile;
		TileType m_type;
		glm::vec3 m_colour;
	};

}

#endif
