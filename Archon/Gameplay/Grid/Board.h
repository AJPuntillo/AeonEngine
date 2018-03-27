#ifndef BOARD_H
#define BOARD_H

#include <AeonEngine/Engine/Rendering/3D/Entity.h>
#include <AeonEngine/Engine/Physics/Stopwatch.h>
#include <AeonEngine/Engine/Audio/Audio.h>
#include <AeonEngine/Engine/Rendering/2D/TextRenderer.h>

#include "Tile.h"
#include "../Pieces/Piece.h"
#include "../Manager/GameManager.h"

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

	enum BoardState
	{
		NONE,
		ATTACKING,
		SELECTION,
	};

	Board();
	Board(int width_, int height_, std::vector<char>& boardLayout_, std::vector<char>& pieceLayout_);
	~Board();

	//Updating and rendering
	void update(const float deltaTime_) override;
	void render(Shader* shader_) override;

	//Game Manager
	void initGameManager(GameManager* gm_);
	//Audio Engine
	void initAudio();

	//Board Controls
	void moveHover(MoveDirection dir_);
	void selectPiece();
	void movePiece(Tile* tile_);
	void attackPiece(Tile* tile_);
	void endTurn();
	void cancel();

	//Getters
	std::vector<Tile*> getBoard() { return m_board; }
	std::vector<Tile*> getAdjacentTiles(Tile* tile_);
	Tile* getTile(glm::vec3 tileCenter_);
	std::vector<Text*> getHUD() { return m_textList; }

	//Special Translate
	void translateBoard(float x, float y, float z);
	Transform transform;

	//Currently Selected Tile/Piece
	Tile* hoveredTile;
	Tile* selectedTile;
	Piece* selectedPiece;
		
	//Reference to P1's last hover and P2's last hover
	Tile* lastHover_P1;
	Tile* lastHover_P2;

private:
	void initBoard();
	void initPiece();

	void updateGameManager();

	void newHover(Tile* newTile_);

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
	
	//Board Utility
	//Attacking
	void GetAllPossibleTargets(Tile* tile_, Piece* piece_);
	void ClearEnemyList();
	std::vector<Tile*> enemyList;
	int hov = 0;

	//Movement
	void GetAllPossibleMovement(Tile* tile_); 	std::vector<Tile*> tmp1;
	void ClearMovementList();
	std::vector<Tile*> movementList;
	std::vector<Edge> edgeList;
	bool CanPass(Tile* tile_);

	//Selection
	bool m_activeSelection = false;
	bool m_isAttacking = false;

	//Gameover
	bool gameover = false;
	void GameOver(GameManager::PlayerTurn victor_);

	//State of the board
	BoardState m_boardState = BoardState::NONE;

	//GameManager reference
	GameManager* m_gameManager;

	//Stopwatch for lerping movement
	Stopwatch* m_timer;

	//Music & SFX
	Audio m_audioEngine;
	Music bg_music;
	Music victory_music;
	SoundEffect sfx_attack;
	SoundEffect sfx_attack_fire;
	SoundEffect sfx_attack_water;
	SoundEffect sfx_attack_earth;
	SoundEffect sfx_victory;
	SoundEffect sfx_movePiece;
	SoundEffect sfx_killPiece;
	SoundEffect sfx_endTurn;
	SoundEffect sfx_moveHover;
	SoundEffect sfx_select;
	SoundEffect sfx_cancel;

	//Text
	void updateHUD();
	std::vector<Text*> m_textList;
	Text* text_hoverHP;
	Text* text_time;
	Text* text_gameover;
	Text* text_hoverDamage;
	Text* text_hoverRange;
	Text* text_hoverEffective;
	Text* text_triangle;
	Text* text_actionCount;

	//Action Counter
	void removeActions();
	int actions = 2;
};

#endif
