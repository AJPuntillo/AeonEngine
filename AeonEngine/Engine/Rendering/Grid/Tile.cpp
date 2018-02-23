#include "Tile.h"

using namespace AEON_ENGINE;

Tile::Tile(int tileType_, bool isPrimitive)
{
	if (isPrimitive) {
		m_tile = new Model(Mesh::PrimitiveType::CUBE);
	}
	else {
		switch (tileType_) {
		case 0:
			m_tile = new Model("Resources/Models/Cube/cube_grass.obj");
			m_type = TileType::GRASS;
			break;
		case 1:
			m_tile = new Model("Resources/Models/Cube/cube_lava.obj");
			m_type = TileType::LAVA;
			break;
		case 2:
			m_tile = new Model("Resources/Models/Cube/cube_forest.obj");
			m_type = TileType::FOREST;
			break;
		case 3:
			m_tile = new Model("Resources/Models/Cube/cube_mountain.obj");
			m_type = TileType::MOUNTAIN;
			break;
		}
	}
	setupTile();
}

Tile::~Tile()
{
	//Empty
}

void Tile::update(const float deltaTime_)
{
	
}

void Tile::render(Shader* shader_)
{
	//Set the Model matrix
	transform.updateModelMatrix();

	//Must be disabled when parenting the tiles to the Board; This will use the tile's original modelmatrix and not the matrix parented to the board
	//shader_->setMat4("model", transform.modelMatrix);

	m_tile->render(shader_);
}

void Tile::setupTile()
{
	//Setup the tile's properties
	m_bound = new BoundingVolume();
	m_bound->setupVolume((Model*)m_tile);
	calcCenterPosition();
	calcOffsets();
	transform = Transform();
}

void Tile::calcCenterPosition()
{
	//Calculate the center position of the bounding volume based on the Min and Max values
	//Subtract the Min from the Max
	m_centerPos = m_bound->getMaxCorner() - m_bound->getMinCorner();
	//Divide the result's X and Z in half (We want to position to be Top-Center)
	if (m_centerPos.x != 0.0f)
		m_centerPos.x /= 2.0f;
	if (m_centerPos.z != 0.0f)
		m_centerPos.z /= 2.0f;
	//Add the resulting vector to the Min
	m_centerPos += m_bound->getMinCorner();

	std::cout << "CenterPos: " << m_centerPos.x << " " << m_centerPos.y << " " << m_centerPos.z << std::endl;
}

void Tile::calcOffsets()
{
	//Calculate the offsets of the bounding volume
	m_xOffset = m_bound->getMaxCorner().x - m_bound->getMinCorner().x;
	m_zOffset = m_bound->getMaxCorner().z - m_bound->getMinCorner().z;
}

void Tile::translateTile(float x, float y, float z) {
	//When the tile is translated, the bounding volume must be translated as well
	transform.translateBy(x, y, z);
	m_bound->movedBy(glm::vec3(x, y, z));
	std::cout << m_bound->getMaxCorner().x << " " << m_bound->getMaxCorner().y << " " << m_bound->getMaxCorner().z << std::endl;
	std::cout << m_bound->getMinCorner().x << " " << m_bound->getMinCorner().y << " " << m_bound->getMinCorner().z << std::endl;

	//The center position must also be recalculated
	calcCenterPosition();
}