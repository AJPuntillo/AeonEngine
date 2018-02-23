#include "Board.h"

using namespace AEON_ENGINE;

Board::Board() :
	m_width(8),
	m_height(8)
{
	initBoard();
}

Board::Board(int width_, int height_, std::string modelPath_) :
	m_width(width_),
	m_height(height_),
	m_modelPath(modelPath_)
{
	initBoard();
}

Board::~Board()
{

}

void Board::update(const float deltaTime_)
{

}

void Board::render(Shader* shader_)
{
	//Set the Model matrix
	transform.updateModelMatrix();

	//Multiply the tile's matrix to the board's matrix to parent it to the board
	for (unsigned int i = 0; i < m_board.size(); i++) {
		shader_->setMat4("model", transform.modelMatrix * m_board[i]->transform.modelMatrix); //Parenting the tiles to the board
		m_board[i]->render(shader_);
	}
}

void Board::initBoard()
{
	int boardLayout[8][8] = {
		{0, 0, 1, 0, 0, 0, 0, 0},
		{0, 2, 0, 1, 0, 0, 1, 0},
		{0, 0, 0, 2, 0, 3, 0, 0},
		{0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 3, 0},
		{2, 0, 3, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 0}
	};

	//Initialize the board with as many tiles specified for the width and height
	//A tile is loaded in, given a position based on it's offset in the loop and then pushed into the board vector
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Tile* tile = new Tile(boardLayout[y][x]);
			tile->translateTile((tile->m_xOffset) * x, 0.0f, (tile->m_zOffset) * y);
			m_board.push_back(tile);
		}
	}
}

void Board::translateBoard(float x, float y, float z)
{
	//When the board is translated, the center positions and bounding volumes of every tile must also be translated as well
	for (int i = 0; i < m_board.size(); i++) {
		m_board[i]->m_centerPos += glm::vec3(x, y, z);
		m_board[i]->m_bound->movedBy(glm::vec3(x, y, z));
	}

	transform.translateBy(x, y, z);
}