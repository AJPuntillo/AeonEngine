#ifndef TILE_H
#define TILE_H

#include <AeonEngine/Engine/Rendering/3D/Entity.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Transform.h>
#include <AeonEngine/Engine/Physics/BoundingVolume.h>

using namespace AEON_ENGINE;

class Tile;
class Edge
{
public:
	Edge(Tile* tile, float w = 1);

	Tile* connectedTo;
	float weight;
};

class Tile : public Entity
{
public:

	enum TileType
	{
		GRASS,
		MOUNTAIN,
		FOREST,
		LAVA
	};
		
	enum OccupationType {
		PIECE,
		OBSTACLE,
		NONE
	};

	Tile();
	Tile(int tileType_, bool isPrimitive = false);
	~Tile();

	//Updating and rendering
	void update(const float deltaTime_) override;
	void render(Shader* shader_) override;

	//Add edge to tile
	void addEdge(Edge e);

	void translateTile(float x, float y, float z);
	Transform transform;

	std::vector<Edge> m_edges;
	BoundingVolume* m_bound;
	glm::vec3 m_centerPos;
	float m_xOffset = 0; //Width of bounding volume
	float m_zOffset = 0; //Length of bounding volume

	//Getters
	TileType getTileType() { return m_type; }

	//Hover colour
	glm::vec3 m_colour = glm::vec3(0.3f, 0.3f, 0.8f);

	//Public Tile properties
	OccupationType m_occ = OccupationType::NONE;
	bool isOccupied = false;
	bool isHovered = false;
	bool isSelected = false;

protected:
	void setupTile();
	void calcCenterPosition();
	void calcOffsets();

	Model* m_tile;

	//Tile properties
	TileType m_type;
};

#endif
