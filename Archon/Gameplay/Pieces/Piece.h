#ifndef PIECE_H
#define PIECE_H

#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Transform.h>
#include "../Grid/Tile.h"

using namespace AEON_ENGINE;

class Piece : public Entity
{
public:
	Piece(int pieceType_);
	~Piece();

	//Updating and rendering
	void update(const float deltaTime_) override;
	void render(Shader* shader_) override;

	Transform transform;

	void movePiece(Tile* moveTo_);

	Tile* currentTile;

private:
	Model* m_model;
};

#endif