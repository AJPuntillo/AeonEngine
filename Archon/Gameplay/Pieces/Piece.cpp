#include "Piece.h"

Piece::Piece(int pieceType_)
{
	switch (pieceType_) {
	//**Team 1 Pieces**
	//Earth
	case 1:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		break;
	//Water
	case 2:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		break;
	//Fire
	case 3:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		break;
	//**Team 2 Pieces**
	//Earth
	case 4:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(-90.0f, 0.0f, 1.0f, 0.0f);
		break;
	//Water
	case 5:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(-90.0f, 0.0f, 1.0f, 0.0f);
		break;
	//Fire
	case 6:
		m_model = new Model("Resources/Models/Piece/TestPiece.obj");
		transform.rotateBy(-90.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 0:
		break;
	}
}

Piece::~Piece()
{

}

void Piece::update(const float deltaTime_)
{

}

void Piece::movePiece(Tile* moveTo_)
{
	currentTile = moveTo_;
	transform.setPosition(moveTo_->m_centerPos);
}

void Piece::render(Shader* shader_)
{
	//Set the Model matrix
	transform.updateModelMatrix();

	shader_->setMat4("model", transform.modelMatrix);

	m_model->render(shader_);
}