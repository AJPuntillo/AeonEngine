#include "Board.h"

using namespace AEON_ENGINE;

Board::Board() :
	m_width(8),
	m_height(8)
{
	initBoard();
	initPiece();
}

Board::Board(int width_, int height_, std::vector<char>& boardLayout_, std::vector<char>& pieceLayout_) :
	m_width(width_),
	m_height(height_),
	m_boardLayout(boardLayout_),
	m_pieceLayout(pieceLayout_)
{
	initBoard();
	initPiece();
}

Board::~Board()
{

}

void Board::update(const float deltaTime_)
{
	for (Tile* tile : m_board)
		tile->update(deltaTime_);

	//For when you're hovering over a selected tile
	if (selectedTile == hoveredTile) {
		hoveredTile->m_colour = glm::vec3(0.0f, 0.8f, 0.8f);
	}
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

	for (unsigned int i = 0; i < p1_pieces.size(); i++) {
		shader_->setMat4("model", transform.modelMatrix * p1_pieces[i]->transform.modelMatrix);
		p1_pieces[i]->render(shader_);
	}

	for (unsigned int i = 0; i < p2_pieces.size(); i++) {
		shader_->setMat4("model", transform.modelMatrix * p2_pieces[i]->transform.modelMatrix);
		p2_pieces[i]->render(shader_);
	}
}

void Board::moveHover(MoveDirection dir_)
{
	//Temp attacking hover
	if (m_isAttacking) {
		if (dir_ == RIGHT) {
			hov--;
			if (hov < 0)
				hov = enemyTiles.size() - 1;
			std::cout << hov << std::endl;
			hoveredTile->isHovered = false;
			hoveredTile = enemyTiles[hov];
			hoveredTile->isHovered = true;
		}

		if (dir_ == LEFT) {
			hov++;
			if (hov > enemyTiles.size() - 1)
				hov = 0;
			std::cout << hov << std::endl;
			hoveredTile->isHovered = false;
			hoveredTile = enemyTiles[hov];
			hoveredTile->isHovered = true;
		}
		//hov = 0;
	}
	else {

		if (dir_ == UP)
			if (hoveredTile->m_edges.size() != 0) {
				//***Old way of searching for an appropriate edge, but not sure if this is slower or faster. Will have to test more!***
				//Tile* toTile = getTile(hoveredTile->m_centerPos - glm::vec3(0.0f, 0.0f, hoveredTile->m_zOffset));
				//if (toTile != nullptr) {
				//	std::cout << "THERE IS A TILE THERE" << std::endl;
				//}

				for (Edge edge : hoveredTile->m_edges) {
					if (edge.connectedTo->m_centerPos.z < hoveredTile->m_centerPos.z && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE) {
						hoveredTile->isHovered = false;
						hoveredTile->m_colour = glm::vec3(0.3f, 0.3f, 0.8f);
						hoveredTile = edge.connectedTo;
						hoveredTile->isHovered = true;
						hoveredTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
						if (m_activeSelection)
							selectedTile->m_colour = glm::vec3(0.3f, 0.8f, 0.3f);
					}
				}
			}

		if (dir_ == DOWN) {
			if (hoveredTile->m_edges.size() != 0) {
				for (Edge edge : hoveredTile->m_edges) {
					if (edge.connectedTo->m_centerPos.z > hoveredTile->m_centerPos.z  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE) {
						hoveredTile->isHovered = false;
						hoveredTile->m_colour = glm::vec3(0.3f, 0.3f, 0.8f);
						hoveredTile = edge.connectedTo;
						hoveredTile->isHovered = true;
						hoveredTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
						if (m_activeSelection)
							selectedTile->m_colour = glm::vec3(0.3f, 0.8f, 0.3f);
					}
				}
			}
		}

		if (dir_ == LEFT) {
			if (hoveredTile->m_edges.size() != 0) {
				for (Edge edge : hoveredTile->m_edges) {
					if (edge.connectedTo->m_centerPos.x < hoveredTile->m_centerPos.x  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE) {
						hoveredTile->isHovered = false;
						hoveredTile->m_colour = glm::vec3(0.3f, 0.3f, 0.8f);
						hoveredTile = edge.connectedTo;
						hoveredTile->isHovered = true;
						hoveredTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
						if (m_activeSelection)
							selectedTile->m_colour = glm::vec3(0.3f, 0.8f, 0.3f);
					}
				}
			}
		}

		if (dir_ == RIGHT) {
			if (hoveredTile->m_edges.size() != 0) {
				for (Edge edge : hoveredTile->m_edges) {
					if (edge.connectedTo->m_centerPos.x > hoveredTile->m_centerPos.x  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE) {
						hoveredTile->isHovered = false;
						hoveredTile->m_colour = glm::vec3(0.3f, 0.3f, 0.8f);
						hoveredTile = edge.connectedTo;
						hoveredTile->isHovered = true;
						hoveredTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
						if (m_activeSelection)
							selectedTile->m_colour = glm::vec3(0.3f, 0.8f, 0.3f);
					}
				}
			}
		}
	}
}

void Board::selectPiece()
{
	if (m_isAttacking) {
		attackPiece(hoveredTile);
		m_isAttacking = false;
		hov = 0;
		enemyTiles.clear();
		return;
	}

	//If there is already an active selection
	if (m_activeSelection) {
		//If the selected tile is itself, then unselect it
		if (selectedTile == hoveredTile) {
			selectedTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
			selectedTile->isSelected = false;
			m_activeSelection = false;
			selectedTile = nullptr;
		}
		else {
			if (!hoveredTile->isOccupied) {
				//Check if there are any adjacent pieces to the tiles and push to a vector is there are
				//std::vector<Tile*> enemyTiles;
				for (Edge edge : hoveredTile->m_edges) {
					//Will need to check if piece is enemy
					if (edge.connectedTo->m_occ == Tile::OccupationType::PIECE && edge.connectedTo != selectedTile)
						enemyTiles.push_back(edge.connectedTo);
				}

				//Display playable options
				int tmp;
				std::cout << "What would you like to do?" << std::endl;
				std::cout << "1: Move" << std::endl;

				//If there are any enemies nearby, allow player to attack
				if (enemyTiles.size() > 0) {
					std::cout << "2: Attack" << std::endl;
				}

				std::cin >> tmp;

				if (tmp == 1)
					movePiece(hoveredTile);
				else if (tmp == 2) {
					movePiece(hoveredTile);
					m_isAttacking = true;
					hoveredTile->isHovered = false;
					hoveredTile = enemyTiles[0];
					hoveredTile->isHovered = true;
				}

				selectedTile->m_colour = glm::vec3(0.3f, 0.3f, 0.8f);
				selectedTile->isSelected = false;
				m_activeSelection = false;
				selectedTile = nullptr;
			}
		}
	}
	else {
		if (hoveredTile->isOccupied && hoveredTile->m_occ == Tile::OccupationType::PIECE) {
			for (Piece* p1 : p1_pieces) {
				if (p1->currentTile == hoveredTile) {
					selectedPiece = p1;
					selectedTile = p1->currentTile;
				}
			}

			for (Piece* p2 : p2_pieces) {
				if (p2->currentTile == hoveredTile) {
					selectedPiece = p2;
					selectedTile = p2->currentTile;
				}
			}

			//selectedTile = hoveredTile;
			//Will need to check if the piece is playable (not enemy)
			selectedTile->isSelected = true;
			m_activeSelection = true;
			selectedTile->m_colour = glm::vec3(0.3f, 0.8f, 0.3f);
		}
	}
}

void Board::movePiece(Tile* tile_)
{
	selectedPiece->currentTile->m_occ = Tile::OccupationType::NONE;
	selectedPiece->currentTile->isOccupied = false;
	selectedPiece->movePiece(tile_);
	selectedPiece->currentTile->m_occ = Tile::OccupationType::PIECE;
	selectedPiece->currentTile->isOccupied = true;
	selectedPiece = nullptr;
}

void Board::attackPiece(Tile* tile_)
{
	for (int i = 0; i < p1_pieces.size(); i++) {
		if (p1_pieces[i]->currentTile == hoveredTile) {
			p1_pieces.erase(p1_pieces.begin() + i);
			hoveredTile->isOccupied = false;
			hoveredTile->m_occ = Tile::OccupationType::NONE;
		}
	}

	for (int i = 0; i < p2_pieces.size(); i++) {
		if (p2_pieces[2]->currentTile == hoveredTile) {
			p2_pieces.erase(p2_pieces.begin() + i);
			hoveredTile->isOccupied = false;
			hoveredTile->m_occ = Tile::OccupationType::NONE;
		}
	}
}

void Board::initBoard()
{
	//Initialize the board with as many tiles specified for the width and height
	//A tile is loaded in, given a position based on it's offset in the loop and then pushed into the board vector
	//The tile type given is based on the vector of chars that were passed in, the loop reads each char and determines the type from that
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Tile* tile = new Tile(m_boardLayout.at((y * m_width) + x));
			tile->translateTile((tile->m_xOffset) * x, 0.0f, (tile->m_zOffset) * y);
			m_board.push_back(tile);
		}
	}

	//Calculating all adjacent tile for each tile on the Z axis
	for (auto fromTile : m_board) {
		Tile* toTile = getTile(fromTile->m_centerPos + glm::vec3(0.0f, 0.0f, fromTile->m_zOffset));
		if (toTile != nullptr) {
			Edge e1(toTile);
			Edge e2(fromTile);
			fromTile->addEdge(e1);
			toTile->addEdge(e2);
		}
	}

	//Calculating all adjacent tile for each tile on the X axis
	for (auto fromTile : m_board) {
		Tile* toTile = getTile(fromTile->m_centerPos + glm::vec3(fromTile->m_xOffset, 0.0f, 0.0f));
		if (toTile != nullptr) {
			Edge e1(toTile);
			Edge e2(fromTile);
			fromTile->addEdge(e1);
			toTile->addEdge(e2);
		}
	}

	//Set first tile to be hovered ** possibly change later
	hoveredTile = m_board[0];
	hoveredTile->m_occ = Tile::OccupationType::PIECE;
	hoveredTile->isHovered = true;
	hoveredTile->isOccupied = true;
	hoveredTile->m_colour = glm::vec3(0.8f, 0.3f, 0.3f);
}

void Board::initPiece()
{
	for (int i = 0; i < m_board.size(); i++) {
		if (m_pieceLayout.at(i) != 0) {
			//Initialize the piece type and position it to the correct tile
			Piece* piece = new Piece(m_pieceLayout.at(i));
			piece->movePiece(m_board[i]);
			piece->currentTile = m_board[i];
			m_board[i]->m_occ = Tile::OccupationType::PIECE;
			m_board[i]->isOccupied = true;

			//Sort the appropriate pieces into their respective vector
			switch (m_pieceLayout.at(i)) {
			case 1:
			case 2:
			case 3:
				p1_pieces.push_back(piece);
				break;
			case 4:
			case 5:
			case 6:
				p2_pieces.push_back(piece);
				break;
			}
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

	for (Piece* piece : p1_pieces) {
		piece->movePiece(piece->currentTile);
	}

	for (Piece* piece : p2_pieces) {
		piece->movePiece(piece->currentTile);
	}

	transform.translateBy(x, y, z);
}

std::vector<Tile*> Board::getAdjacentTiles(Tile* tile_)
{
	std::vector<Tile*> adjacentNodes;
	for (auto e : tile_->m_edges)
	{
		adjacentNodes.push_back(e.connectedTo);
	}

	return adjacentNodes;
}

Tile* Board::getTile(glm::vec3 tileCenter_)
{
	for (Tile* tile : m_board)
	{
		if (tile->m_centerPos == tileCenter_)
			return tile;
	}
	return nullptr;
}