#ifndef BOARD_H
#define BOARD_H

#include <AeonEngine/Engine/Rendering/3D/Entity.h>

#include "Tile.h"
#include "../Pieces/Piece.h"

using namespace AEON_ENGINE;

class Board : public Entity
{
public:
	enum MoveDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Board();
	Board(int width_, int height_, std::vector<char>& boardLayout_, std::vector<char>& pieceLayout_);
	~Board();

	//Updating and rendering
	void update(const float deltaTime_) override;
	void render(Shader* shader_) override;

	//Board Controls
	void moveHover(MoveDirection dir_);
	void selectPiece();
	void movePiece(Tile* tile_);
	void attackPiece(Tile* tile_);

	//Getters
	std::vector<Tile*> getBoard() { return m_board; }
	std::vector<Tile*> getAdjacentTiles(Tile* tile_);
	Tile* getTile(glm::vec3 tileCenter_);

	//Special Translate
	void translateBoard(float x, float y, float z);
	Transform transform;

	//Currently Selected Tile/Piece
	Tile* hoveredTile;
	Tile* selectedTile;
	Piece* selectedPiece;
		
	//Reference to P1's last hover and P2's last hover

private:
	void initBoard();
	void initPiece();

	//Container of tiles
	std::vector<Tile*> m_board;

	//Container of pieces
	std::vector<Piece*> p1_pieces;
	std::vector<Piece*> p2_pieces;

	//Vector of chars to contain the board layout
	std::vector<char> m_boardLayout;
	std::vector<char> m_pieceLayout;

	//Board size
	int m_width = 0;
	int m_height = 0;
		
	//Selection
	bool m_activeSelection = false;
	bool m_isAttacking = false;

	//Enemy tile container (For Attacking)
	std::vector<Tile*> enemyTiles;
	int hov = 0;
};

#endif
