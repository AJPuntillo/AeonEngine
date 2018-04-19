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
	initAudio();

	m_timer = new Stopwatch();

	text_hoverHP = new Text(" ", 20, 70, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_hoverHP);
	text_hoverDamage = new Text(" ", 20, 50, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_hoverDamage);
	text_hoverRange = new Text(" ", 20, 30, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_hoverRange);
	text_hoverEffective = new Text(" ", 20, 10, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_hoverEffective);
	//text_selectHP = new Text("Selected Piece HP: ", 10, 40, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	//m_textList.push_back(text_selectHP);
	text_time = new Text("Time: 45", 710, 10, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_time);
	text_actionCount = new Text("Actions: ", 710, 30, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_actionCount);
}

Board::~Board()
{
	bg_music.stop();
	victory_music.stop();

	selectedPiece = nullptr;

	selectedTile = nullptr;

	hoveredTile = nullptr;

	for (Tile* tile : m_board) {
		delete tile;
		tile = nullptr;
	}

	for (Piece* p1 : p1_pieces) {
		delete p1;
		p1 = nullptr;
	}

	for (Piece* p2 : p2_pieces) {
		delete p2;
		p2 = nullptr;
	}
}

void Board::update(const float deltaTime_)
{
	for (Tile* tile : m_board)
		tile->update(deltaTime_);

	for (Piece* p1 : p1_pieces)
		p1->update(deltaTime_);

	for (Piece* p2 : p2_pieces)
		p2->update(deltaTime_);

	m_timer->Update(deltaTime_);

	//Turn Timer
	if (m_gameManager->m_turnTimer->getTimerValue() == m_gameManager->m_turnMaxTime) {
		endTurn();
	}

	if (m_gameManager->p1_pieceCount == 0) {
		GameOver(GameManager::PlayerTurn::P2_turn);
	}
	else if (m_gameManager->p2_pieceCount == 0) {
		GameOver(GameManager::PlayerTurn::P1_turn);
	}

	if (actions == 0)
		removeActions();

	updateHUD();
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
	if (gameover)
		return;

	switch (m_boardState) {
		case BoardState::NONE:
		case BoardState::SELECTION:
			if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
				if (dir_ == LEFT)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.z < hoveredTile->m_centerPos.z)
								newHover(edge.connectedTo);

				if (dir_ == RIGHT)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.z > hoveredTile->m_centerPos.z)
								newHover(edge.connectedTo);

				if (dir_ == DOWN)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.x < hoveredTile->m_centerPos.x)
								newHover(edge.connectedTo);

				if (dir_ == UP)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.x > hoveredTile->m_centerPos.x)
								newHover(edge.connectedTo);
			}
			else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
				if (dir_ == RIGHT)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.z < hoveredTile->m_centerPos.z)
								newHover(edge.connectedTo);

				if (dir_ == LEFT)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.z > hoveredTile->m_centerPos.z)
								newHover(edge.connectedTo);

				if (dir_ == UP)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.x < hoveredTile->m_centerPos.x)
								newHover(edge.connectedTo);

				if (dir_ == DOWN)
					if (hoveredTile->m_edges.size() != 0)
						for (Edge edge : hoveredTile->m_edges)
							if (edge.connectedTo->m_centerPos.x > hoveredTile->m_centerPos.x)
								newHover(edge.connectedTo);
			}

			/*if (dir_ == UP)
				if (hoveredTile->m_edges.size() != 0)
					for (Edge edge : hoveredTile->m_edges)
						if (edge.connectedTo->m_centerPos.z < hoveredTile->m_centerPos.z && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE)
							newHover(edge.connectedTo);

			if (dir_ == DOWN)
				if (hoveredTile->m_edges.size() != 0)
					for (Edge edge : hoveredTile->m_edges)
						if (edge.connectedTo->m_centerPos.z > hoveredTile->m_centerPos.z  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE)
							newHover(edge.connectedTo);

			if (dir_ == LEFT)
				if (hoveredTile->m_edges.size() != 0)
					for (Edge edge : hoveredTile->m_edges)
						if (edge.connectedTo->m_centerPos.x < hoveredTile->m_centerPos.x  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE)
							newHover(edge.connectedTo);

			if (dir_ == RIGHT)
				if (hoveredTile->m_edges.size() != 0)
					for (Edge edge : hoveredTile->m_edges)
						if (edge.connectedTo->m_centerPos.x > hoveredTile->m_centerPos.x  && edge.connectedTo->m_occ != Tile::OccupationType::OBSTACLE)
							newHover(edge.connectedTo);*/

			break;

		case BoardState::ATTACKING:
			if (dir_ == RIGHT) {
				hov--;
				if (hov < 0)
					hov = enemyList.size() - 1;
				newHover(enemyList[hov]);
			}

			if (dir_ == LEFT) {
				hov++;
				if (hov > enemyList.size() - 1)
					hov = 0;
				newHover(enemyList[hov]);
			}
			break;
	}

	//Play move hover sfx
	sfx_moveHover.play(0, 20);
}

void Board::selectPiece()
{
	if (gameover)
		return;

	switch (m_boardState) {
		case BoardState::NONE:
			if (!hoveredTile->IsTileOpen()) { //Might want to check if it's the current player's turn
				if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
					for (Piece* p1 : p1_pieces) {
						if (p1->currentTile == hoveredTile && p1->hasAction) {
							selectedPiece = p1;
							selectedTile = p1->currentTile;
							selectedTile->isSelected = true;
							m_boardState = BoardState::SELECTION;

							GetAllPossibleMovement(selectedTile);
						}
					}
				}
				else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
					for (Piece* p2 : p2_pieces) {
						if (p2->currentTile == hoveredTile && p2->hasAction) {
							selectedPiece = p2;
							selectedTile = p2->currentTile;
							selectedTile->isSelected = true;
							m_boardState = BoardState::SELECTION;

							GetAllPossibleMovement(selectedTile);
						}
					}
				}
				sfx_select.play(0, 20);
			}
			break;

		case BoardState::SELECTION:
			//If the selected tile is itself, check if there are any enemies to attack
			if (selectedTile == hoveredTile) {
				GetAllPossibleTargets(hoveredTile, selectedPiece);
				if (enemyList.size() > 0) {
					m_boardState = BoardState::ATTACKING;
					newHover(enemyList[0]);
					ClearMovementList();
					selectedTile->isSelected = false;
					selectedTile = nullptr;
					standingAttack = true;
				}
			}
			else {
				//if the tile is open AND contained within the pieces's movement (in this case 2 spots)
				if (hoveredTile->IsTileOpen() && std::find(movementList.begin(), movementList.end(), hoveredTile) != movementList.end() && CanPass(hoveredTile)) {
					movePiece(hoveredTile);

					GetAllPossibleTargets(hoveredTile, selectedPiece);
					if (enemyList.size() > 0) {
						m_boardState = BoardState::ATTACKING;
						newHover(enemyList[0]);
					}
					else {
						m_boardState = BoardState::NONE;
					}

					selectedTile->isSelected = false;
					selectedTile = nullptr;
				}
			}
			sfx_select.play(0, 20);
			break;

		case BoardState::ATTACKING:
			attackPiece(hoveredTile);
			m_isAttacking = false;
			m_boardState = BoardState::NONE;
			hov = 0;
			ClearEnemyList();
			ClearMovementList();
			sfx_select.play(0, 20);
			break;
	}
}

void Board::newHover(Tile* newTile_)
{
	//Reset old tile
	hoveredTile->isHovered = false;

	//Set new hover tile
	hoveredTile = newTile_;

	//Give hover tile properties
	hoveredTile->isHovered = true;
}

void Board::movePiece(Tile* tile_)
{
	//Reset piece
	selectedPiece->currentTile->m_occ = Tile::OccupationType::NONE;
	selectedPiece->currentTile->isOccupied = false;

	//Move the piece to the selected tile
	//m_timer->StartTimer(selectedPiece->getWalkSpeed());
	selectedPiece->movePiece(tile_, selectedPiece->getWalkSpeed());

	//Set new tile properties
	selectedPiece->currentTile->m_occ = Tile::OccupationType::PIECE;
	selectedPiece->currentTile->isOccupied = true;

	//Selected piece is unselected
	selectedPiece->hasAction = false;
	//selectedPiece = nullptr;

	//Clear the movement list
	ClearMovementList();

	//Play move sound
	sfx_movePiece.play(0, 100);

	actions--;
}

void Board::attackPiece(Tile* tile_)
{
	if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
		for (int i = 0; i < p1_pieces.size(); i++) {
			if (p1_pieces[i]->currentTile == tile_) {
				float enemyHP = selectedPiece->attackPiece(p1_pieces[i]);
				if (enemyHP <= 0) {
					p1_pieces.erase(p1_pieces.begin() + i);
					tile_->isOccupied = false;
					tile_->m_occ = Tile::OccupationType::NONE;
					sfx_killPiece.play(0, 100);
				}
			}
		}
	}
	else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
		for (int i = 0; i < p2_pieces.size(); i++) {
			if (p2_pieces[i]->currentTile == tile_) {
				float enemyHP = selectedPiece->attackPiece(p2_pieces[i]);
				if (enemyHP <= 0) {
					p2_pieces.erase(p2_pieces.begin() + i);
					tile_->isOccupied = false;
					tile_->m_occ = Tile::OccupationType::NONE;
					sfx_killPiece.play(0, 100);
				}
			}
		}
	}

	m_gameManager->playParticles(selectedPiece->getPieceType(), 100, 3.0f, hoveredTile->m_centerPos);

	//Selected piece is unselected
	selectedPiece->hasAction = false;
	//selectedPiece = nullptr;

	updateGameManager();

	sfx_attack.play(0, 100);

	if (standingAttack) {
		actions--;
		standingAttack = false;
	}
}

void Board::cancel()
{
	switch(m_boardState) {
		case BoardState::NONE:
			//Do nothing
			break;

		case BoardState::SELECTION:
			selectedTile->isSelected = false;
			selectedTile = nullptr;
			m_boardState = BoardState::NONE;
			ClearMovementList();
			sfx_cancel.play(0, 20);
			break;

		case BoardState::ATTACKING:
			m_boardState = BoardState::NONE;
			ClearEnemyList();
			standingAttack = false;
			sfx_cancel.play(0, 20);
			break;
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

	hoveredTile = m_board[0];
	newHover(m_board[0]);
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

void Board::endTurn()
{
	if (m_boardState == BoardState::ATTACKING || m_boardState == BoardState::SELECTION || m_gameManager->m_isAnimating || gameover)
		return;

	m_gameManager->nextTurn();

	if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
		for (Piece* piece : p1_pieces) {
			piece->hasAction = true;
		}

		for (Piece* piece : p2_pieces) {
			piece->hasAction = false;
		}

		lastHover_P2 = hoveredTile;
		newHover(lastHover_P1);
		
	}
	else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
		for (Piece* piece : p1_pieces) {
			piece->hasAction = false;
		}

		for (Piece* piece : p2_pieces) {
			piece->hasAction = true;
		}

		lastHover_P1 = hoveredTile;
		newHover(lastHover_P2);
	}

	sfx_endTurn.play(0, 100);

	actions = 2;
}

void Board::initGameManager(GameManager* gm_)
{
	m_gameManager = gm_;
	updateGameManager();
	lastHover_P1 = hoveredTile;
	endTurn(); //Turn 1
}

void Board::updateGameManager()
{
	m_gameManager->updatePieceCount(p1_pieces.size(), p2_pieces.size());
}

void Board::initAudio()
{
	m_audioEngine.init();

	//Load and play BG music
	bg_music = m_audioEngine.loadMusic("Resources/Audio/Music/Ove_Earth.ogg");
	bg_music.play(-1, 40);

	victory_music = m_audioEngine.loadMusic("Resources/Audio/Music/Ove_Drum.ogg");

	sfx_attack = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/attack_fire.ogg");
	sfx_victory = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/victory.wav");
	sfx_movePiece = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/move_piece.ogg");
	sfx_killPiece = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/death.wav");
	sfx_endTurn = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/end_turn.wav");
	sfx_moveHover = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/click.wav");
	sfx_select = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/selection.wav");
	sfx_cancel = m_audioEngine.loadSoundEffect("Resources/Audio/SFX/cancel.wav");

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

void Board::GetAllPossibleTargets(Tile* tile_, Piece* piece_)
{
	//for (Edge edge : tile_->m_edges) {
	//	//Too sloppy, can be much more clean
	//	if (edge.connectedTo->m_occ == Tile::OccupationType::PIECE && edge.connectedTo != selectedTile) {
	//		if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
	//			for (Piece* p2 : p2_pieces) {
	//				if (p2->currentTile == edge.connectedTo)
	//					enemyList.push_back(edge.connectedTo);
	//			}
	//		}
	//		else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
	//			for (Piece* p1 : p1_pieces) {
	//				if (p1->currentTile == edge.connectedTo)
	//					enemyList.push_back(edge.connectedTo);
	//			}
	//		}
	//	}
	//}

	for (Edge edge : tile_->m_edges) {
		if (edge.connectedTo->m_occ == Tile::OccupationType::PIECE && edge.connectedTo != selectedTile) {
			if (   tile_->m_centerPos + glm::vec3(1.0f, 0.0f, 0.0f) == edge.connectedTo->m_centerPos
				|| tile_->m_centerPos - glm::vec3(1.0f, 0.0f, 0.0f) == edge.connectedTo->m_centerPos
				|| tile_->m_centerPos + glm::vec3(0.0f, 0.0f, 1.0f) == edge.connectedTo->m_centerPos
				|| tile_->m_centerPos - glm::vec3(0.0f, 0.0f, 1.0f) == edge.connectedTo->m_centerPos) {
				if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
					for (Piece* p2 : p2_pieces) {
						if (p2->currentTile == edge.connectedTo)
							enemyList.push_back(edge.connectedTo);
					}
				}
				else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
					for (Piece* p1 : p1_pieces) {
						if (p1->currentTile == edge.connectedTo)
							enemyList.push_back(edge.connectedTo);
					}
				}
			}
		}

		//Ranged Attack
		if (selectedPiece->getAttackRange() == 2) {
			for (Edge outerEdge : edge.connectedTo->m_edges) {
				if (outerEdge.connectedTo != selectedPiece->currentTile) {
					if (!(std::find(enemyList.begin(), enemyList.end(), outerEdge.connectedTo) != enemyList.end()) && outerEdge.connectedTo->m_occ == Tile::OccupationType::PIECE && outerEdge.connectedTo != selectedTile) {
						if (   tile_->m_centerPos + glm::vec3(2.0f, 0.0f, 0.0f) == outerEdge.connectedTo->m_centerPos
							|| tile_->m_centerPos - glm::vec3(2.0f, 0.0f, 0.0f) == outerEdge.connectedTo->m_centerPos
							|| tile_->m_centerPos + glm::vec3(0.0f, 0.0f, 2.0f) == outerEdge.connectedTo->m_centerPos
							|| tile_->m_centerPos - glm::vec3(0.0f, 0.0f, 2.0f) == outerEdge.connectedTo->m_centerPos) {
							if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
								for (Piece* p2 : p2_pieces) {
									if (p2->currentTile == outerEdge.connectedTo)
										enemyList.push_back(outerEdge.connectedTo);
								}
							}
							else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
								for (Piece* p1 : p1_pieces) {
									if (p1->currentTile == outerEdge.connectedTo)
										enemyList.push_back(outerEdge.connectedTo);
								}
							}
						}
					}
				}

				//When empowered by the River
				if (selectedPiece->currentTile->getTileType() == Tile::TileType::RIVER) {
					for (Edge finalEdge : outerEdge.connectedTo->m_edges) {
						if (finalEdge.connectedTo != selectedPiece->currentTile) {
							if (!(std::find(enemyList.begin(), enemyList.end(), finalEdge.connectedTo) != enemyList.end()) && finalEdge.connectedTo->m_occ == Tile::OccupationType::PIECE && finalEdge.connectedTo != selectedTile) {
								if (   tile_->m_centerPos + glm::vec3(3.0f, 0.0f, 0.0f) == finalEdge.connectedTo->m_centerPos
									|| tile_->m_centerPos - glm::vec3(3.0f, 0.0f, 0.0f) == finalEdge.connectedTo->m_centerPos
									|| tile_->m_centerPos + glm::vec3(0.0f, 0.0f, 3.0f) == finalEdge.connectedTo->m_centerPos
									|| tile_->m_centerPos - glm::vec3(0.0f, 0.0f, 3.0f) == finalEdge.connectedTo->m_centerPos) {
									if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
										for (Piece* p2 : p2_pieces) {
											if (p2->currentTile == finalEdge.connectedTo)
												enemyList.push_back(finalEdge.connectedTo);
										}
									}
									else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
										for (Piece* p1 : p1_pieces) {
											if (p1->currentTile == finalEdge.connectedTo)
												enemyList.push_back(finalEdge.connectedTo);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Board::ClearEnemyList()
{
	enemyList.clear();
}
int loopCount = 0;
int movementLimitCounter = 0;
void Board::GetAllPossibleMovement(Tile* tile_)
{
	for (Edge edge : selectedPiece->currentTile->m_edges) {
		if (edge.connectedTo->IsTileOpen() && CanPass(edge.connectedTo)) {
			movementList.push_back(edge.connectedTo);
			edge.connectedTo->isMoveableTo = true;
		}
		else {
			edge.connectedTo->isUnmoveableTo = true;
		}
		if (selectedPiece->getMovement() > 0) {
			for (Edge outerEdge : edge.connectedTo->m_edges) {
				if (outerEdge.connectedTo != selectedPiece->currentTile) {
					if (!(std::find(movementList.begin(), movementList.end(), outerEdge.connectedTo) != movementList.end()) && outerEdge.connectedTo->IsTileOpen() && CanPass(outerEdge.connectedTo)) {
						movementList.push_back(outerEdge.connectedTo);
						outerEdge.connectedTo->isMoveableTo = true;
					}
					else {
						outerEdge.connectedTo->isUnmoveableTo = true;
					}
				}
			}
		}
	}

	//**May want to revsist, makes the method recursive
	//if (loopCount < 2) {
	//	for (Edge edge : tile_->m_edges) {
	//		if (edge.connectedTo->IsTileOpen()) {
	//			movementList.push_back(edge.connectedTo);
	//			edge.connectedTo->isMoveableTo = true;
	//		}
	//		else {
	//			edge.connectedTo->isUnmoveableTo = true;
	//		}
	//		if (selectedPiece->getMovement() > 1) {
	//			for (Edge outerEdge : edge.connectedTo->m_edges) {
	//				if (!(std::find(movementList.begin(), movementList.end(), outerEdge.connectedTo) != movementList.end()) && outerEdge.connectedTo->IsTileOpen()) {
	//					movementList.push_back(outerEdge.connectedTo);
	//					edgeList.push_back(outerEdge);
	//					outerEdge.connectedTo->isMoveableTo = true;
	//				} 
	//				else {
	//					outerEdge.connectedTo->isUnmoveableTo = true;
	//				}
	//			}
	//		}
	//	}
	//	//loopCount++;
	//	//GetAllPossibleMovement(edgeList);
	//}
	//else {
	//	loopCount = 0;
	//	std::cout << edgeList.size() << std::endl;
	//}


	//for (Edge edge : tile_->m_edges) {
	//	if (loopCount < selectedPiece->getMovement()) {
	//		if (!(std::find(movementList.begin(), movementList.end(), edge.connectedTo) != movementList.end()) && edge.connectedTo->IsTileOpen()) {
	//			movementList.push_back(edge.connectedTo);
	//			edge.connectedTo->isMoveableTo = true;
	//			tmp1.push_back(edge.connectedTo);
	//		}
	//		else {
	//			edge.connectedTo->isUnmoveableTo = true;
	//		}
	//	}
	//}
	//loopCount++;
	//for (int i = 0; i < tmp1.size(); i++) {
	//	GetAllPossibleMovement(tmp1[i]);
	//}
}

void Board::ClearMovementList()
{
	//Loops through board, but should only loop through possible movement
	for (Tile* tile : m_board) {
		tile->isMoveableTo = false;
		tile->isUnmoveableTo = false;
	}
	movementList.clear();
}

bool Board::CanPass(Tile* tile_)
{
	if (tile_->getTileType() == Tile::TileType::MOUNTAIN && selectedPiece->getPieceType() == Piece::PieceType::EARTH) {
		return true;
	}
	else if (tile_->getTileType() != Tile::TileType::MOUNTAIN) {
		return true;
	}
	else {
		return false;
	}
}

void Board::GameOver(GameManager::PlayerTurn victor_)
{
	if (!gameover) {
		text_gameover = new Text("", 10, 650, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		if (victor_ == GameManager::PlayerTurn::P1_turn) {
			text_gameover->setText("PLAYER 1 WINS");
		}
		else {
			text_gameover->setText("PLAYER 2 WINS");
		}

		m_textList.push_back(text_gameover);

		sfx_victory.play(0, 80);
		bg_music.stop();
		victory_music.play(-1, 20);

		gameover = true;
	}
}

void Board::updateHUD()
{

	for (Piece* p1 : p1_pieces) {
		if (p1->currentTile == hoveredTile) {
			text_hoverHP->setText("Health: " + std::to_string(p1->getHealth()));
			text_hoverDamage->setText("Damage: " + std::to_string(p1->getAttackDamage()));
			text_hoverRange->setText("Range: " + std::to_string(p1->getAttackRange()));
			text_hoverEffective->setText("Strong: " + p1->getAdv() + "   " + "Weak: " + p1->getWeakness());
		}
	}

	for (Piece* p2 : p2_pieces) {
		if (p2->currentTile == hoveredTile) {
			text_hoverHP->setText("Health: " + std::to_string(p2->getHealth()));
			text_hoverDamage->setText("Damage: " + std::to_string(p2->getAttackDamage()));
			text_hoverRange->setText("Range: " + std::to_string(p2->getAttackRange()));
			text_hoverEffective->setText("Strong: " + p2->getAdv() + "   " + "Weak: " + p2->getWeakness());
		}
	}

	//if (selectedPiece != NULL) {
	//	text_selectHP->setText("Selected Piece HP: " + std::to_string(selectedPiece->getHealth()));
	//}
	//else {
	//	text_selectHP->setText("Selected Piece HP: ");
	//}

	int time = (glm::floor(m_gameManager->m_turnTimer->getTimerValue() - 45) * -1);
	text_time->setText("Time: " + std::to_string(time));

	text_actionCount->setText("Actions: " + std::to_string(actions));
}

void Board::removeActions()
{
	if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P1_turn) {
		for (Piece* piece : p1_pieces) {
			piece->hasAction = false;
		}
	}
	else if (m_gameManager->getPlayerTurn() == GameManager::PlayerTurn::P2_turn) {
		for (Piece* piece : p2_pieces) {
			piece->hasAction = false;
		}
	}
}