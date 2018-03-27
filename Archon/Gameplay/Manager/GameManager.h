#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Physics/Stopwatch.h>
#include <AeonEngine/Engine/Rendering/Particles/ParticleEngine.h>

//#include "../Grid/Board.h"
#include "../Pieces/Piece.h"

using namespace AEON_ENGINE;

class GameManager
{
public:
	enum PlayerTurn {
		P1_turn,
		P2_turn
	};

	GameManager();
	~GameManager();

	void update(float deltaTime_, Camera* camera_);
	void updatePieceCount(int p1_, int p2_);
	void render(Shader* shader_);

	//Controls
	//void move(Board::MoveDirection dir_);
	//void select();
	//void unselect();
	void nextTurn();
	void playParticles(Piece::PieceType type_, int amount_, float lifeTime_, glm::vec3 pos_);

	//For camera animation
	bool m_isAnimating = false;

	//Getters
	PlayerTurn getPlayerTurn() { return m_playerTurn; }

	int p1_pieceCount;
	int p2_pieceCount;
	
	//Turns
	int turnCount = 0;
	Stopwatch* m_turnTimer;
	float m_turnMaxTime = 45.0f;

	//Particles
	ParticleEmitter* m_emitter;


private:
	//Keep track of player turns
	PlayerTurn m_playerTurn = PlayerTurn::P2_turn;

	float m_timer = 0.0f;
};

#endif